/*
 * https://www.hackerrank.com/companies/vmware/challenges/hierarchical-page-table-translation
 */

/*
 *  Jai (jai_97@rediffmail.com)
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAIN 1
#define READPHYS 1
#define DEBUG 1

#if DEBUG
#define debug(x) printf x
#else
#define debug(x)
#endif

/*
 * readPhys --
 *   Read an aligned 32bit value from physical memory.
 */
static uint32_t readPhys(uint32_t physAddr);

enum access {
   ACCESS_READ = 1,
   ACCESS_WRITE = 2,
   ACCESS_EXECUTE = 3,
};

enum fault {
   FAULT_NONE = 0,
   FAULT_NOT_PRESENT = 1,
   FAULT_MALFORMED = 2,
   FAULT_VIOLATION = 3,
};

enum leafPageType {
  LEAF_4G = 1,
  LEAF_4M = 2,
  LEAF_4K = 3,
};

struct Fault_ {
  enum fault flt;
  char *name;
} Fault[4]  = { {FAULT_NONE, "NONE"}, {FAULT_NOT_PRESENT, "NOT_PRESENT"}, {FAULT_MALFORMED, "MALFORMED" }, {FAULT_VIOLATION, "VIOLATION" } };

#define FOURK (4096)
#define PRESENT(a) (a & 1)
#define READ(a) ((a >> 1) & 1)
#define WRITE(a) ((a >> 2) & 1)
#define EXEC(a) ((a >> 3) & 1)
#define LEAF(a) ((a >> 4) & 1)

#define PL2_BASE(a) ((a >> 12) *FOURK)     // pl2 base = upper 20 bits of pl3 *4k (pl3 contains the PPN for pl2 table)
#define PL2_IDX(l) ((l >> 22) & 0x3FF)   // pl2 index = upper most 10 bits in linear add
#define PL2_PPN_ADDR(a, l) (PL2_BASE(a) + PL2_IDX(l)*sizeof(uint32_t))        // offset of pl2 entry in pl2 table = pl2 base + pl2 index *8
#define PL2_PPN(a,l) (readPhys(PL2_PPN_ADDR(a,l)))
// a = pl3e
#define PL2E(a, l) (PL2_PPN(a,l) )
#define PL1_IDX(l) ((l >> 12) & 0x3FF)      // middle 10 bits in the linear addr is the index 
// a = pl2e = base of PL1 from above
#define PL1_BASE(a)  ((a >> 12) *FOURK) 
#define PL1_PPN_ADDR(a, l) (PL1_BASE(a) + PL1_IDX(l) * sizeof(uint32_t))
#define PL1_PPN(a,l) (readPhys(PL1_PPN_ADDR(a,l))) 
#define PL1E(a, l) (PL1_PPN(a,l) )

// macros for checking present, malformed, access
// a = addr
#define CHECK_PRESENT(a) do { \
if ( (flt = check_present(a)) != FAULT_NONE) \
  return flt;\
} while(0)

// a = addr, type = leaf type
#define CHECK_VALID(a, type) do { \
if ( (flt = check_valid(a, type)) != FAULT_NONE) \
  return flt;\
} while(0)

// a = addr, x = access
#define CHECK_ACCESS(a,x)  do { \
if ( (flt = check_access(a, x)) != FAULT_NONE) \
  return flt;\
} while(0)

#define INC_NADDRS (32)

#if READPHYS
typedef struct _physMem {
  uint32_t addr;
  uint32_t value;
} physMem;

physMem *gphysMem = NULL;
int cur_addrs_max = INC_NADDRS; 
  
static 
uint32_t readPhys(uint32_t physAddr)
{
  physMem *ptr = gphysMem;
  int i = 0;
  while (i < cur_addrs_max) {
    if (ptr->addr == physAddr)
      return ptr->value;
    ptr++;
    i++;
  }
  printf("readPhys failed at %x\n", physAddr);
  assert(0);
}
#endif

static enum fault
check_present(uint32_t addr)
{
  if (!PRESENT(addr))
    return FAULT_NOT_PRESENT;
  return FAULT_NONE;
}

static enum fault
check_access(uint32_t addr, enum access access)
{
  debug(("check_access: addr %x access %d \n", addr, access));
  switch(access) {
    case ACCESS_READ:
      if (!READ(addr))
        return FAULT_VIOLATION;
      break;
    case ACCESS_WRITE:
      if (!WRITE(addr))
        return FAULT_VIOLATION;
      break;
    case ACCESS_EXECUTE:
      if (!EXEC(addr))
        return FAULT_VIOLATION;
      break;
    default:
      printf("illegal access type %d\n", access);
      assert(0);
  }
  return FAULT_NONE;
}

static enum fault
check_valid(uint32_t addr, enum leafPageType type)
{
  debug(("check_valid: addr %x type %d \n", addr, type));
  switch(type) {
    case LEAF_4G:
      if ((addr >> 12) != 0) 
        return FAULT_MALFORMED;
      break;
    case LEAF_4M:
     if ( ((addr >> 12) & 0x3FF) != 0) 
        return FAULT_MALFORMED;
      break;
    case LEAF_4K:
     if (!LEAF(addr))  
        return FAULT_MALFORMED;
      break;
    default:
      printf("illegal leafpage type %d\n", type);
      assert(0);
  }    
  return FAULT_NONE;
}


/*
 * linearToPhys()
 *   Traverse the page tables rooted at pl3e for the linearAddr and access type.
 *   Input:
 *       pl3e - The contents of the PL3e register.
 *       linearAddr - The linear address being accessed.
 *       access - ACCESS_READ, ACCESS_WRITE, or ACCESS_EXECUTE.
 *   Return:
 *       FAULT_NONE on success.
 *       Otherwise FAULT_NOT_PRESENT, FAULT_MALFORMED, or FAULT_VIOLATION.
 *   Output:
 *       On success, populate *physAddr.
 */
static enum fault
linearToPhys(uint32_t pl3e, uint32_t linearAddr, enum access access,
             uint32_t *physAddr /* OUT */)
{
   /* !!! PUT YOUR CODE HERE !!! */
  enum fault flt;     // needed by the CHECK macros
  uint32_t pl2e, pl1e;

  debug(("linearToPhy: pl3e %x addr %x access %d \n", pl3e, linearAddr, access));
  if (LEAF(pl3e)) { // leaf 4G 
    // leaf - so check present and well formed
    CHECK_PRESENT(pl3e);
    CHECK_VALID(pl3e, LEAF_4G);
    CHECK_ACCESS(pl3e, access);   // Jai
    *physAddr = (linearAddr);
  } else { 
    // pl2e = phys addr of base of pl1 table
    pl2e = PL2E(pl3e, linearAddr);
    debug(("pl2e %x \n", pl2e));

    if (LEAF(pl2e)) { // leaf 4MB
      // leaf - so check present and well formed, and then access on pl3e
      CHECK_PRESENT(pl2e);
      CHECK_VALID(pl2e, LEAF_4M);
      CHECK_ACCESS(pl3e, access);
      CHECK_ACCESS(pl2e, access);   // Jai
      *physAddr = ( ((pl2e >> 22) << 22) | (linearAddr & 0x3FFFFF));
      return FAULT_NONE;
    }
    // must be a leaf 4K
    pl1e = PL1E(pl2e, linearAddr);     //  PPN of the 4K page
    debug(("pl1e %x \n", pl1e));

    // check present on pl3e, pl2e, pl1e, and then malformed for pl1e (only leaf here) and then access on pl3e, pl2e, pl1e
    CHECK_PRESENT(pl3e);
    CHECK_PRESENT(pl2e);
    CHECK_PRESENT(pl1e);
    // well formed check on leaf 4K
    CHECK_VALID(pl1e, LEAF_4K);
    // access on all
    CHECK_ACCESS(pl3e, access);
    CHECK_ACCESS(pl2e, access);
    CHECK_ACCESS(pl1e, access);

    *physAddr = ( ((pl1e >> 12) << 12) | (linearAddr & 0xFFF));
  }
  return FAULT_NONE;

}

#if MAIN
int
main()
{
  char *linep = NULL;
  size_t linecap = 0;
  ssize_t  len;
  char temp[64];
  uint32_t pl3e, addr, val, phys;
  enum fault fault;

  int cur_addrs = 0;

  if ( (gphysMem = calloc(cur_addrs_max, sizeof(physMem))) == NULL) {
    perror("calloc");
    exit(1);
  }
 
  while ( (len = getline(&linep, &linecap, stdin)) > 0) {
    // printf("len %ld %s\n", len, linep);
    while(isspace(*linep))
      linep++;

    if (*linep == 0 || *linep == '#')
        continue;
  
    if (strstr(linep, "pl3e")) {
      sscanf(linep, "%s %x", temp, &pl3e);
    } else if (strstr(linep, "memory")) {
      sscanf(linep, "%s %x = %x", temp, &addr, &val);   
      if (cur_addrs == cur_addrs_max) {
        cur_addrs_max += INC_NADDRS;
        if ( (gphysMem = realloc(gphysMem, cur_addrs_max * sizeof(physMem))) == NULL) {

        }
      }
        
      gphysMem[cur_addrs].addr = addr;
      gphysMem[cur_addrs].value = val;
      cur_addrs++;
    } else if (strstr(linep, "read")) {
      sscanf(linep, "%s %x", temp, &addr);
      if ( (fault = linearToPhys(pl3e, addr, ACCESS_READ, &phys)) != FAULT_NONE) {
        printf("read %x -> %s\n", addr, Fault[fault].name);         
        continue; 
      }
      printf("read %x -> %x\n", addr, phys);
    } else if (strstr(linep, "write")) {
      sscanf(linep, "%s %x", temp, &addr);
      if ( (fault = linearToPhys(pl3e, addr, ACCESS_WRITE, &phys)) != FAULT_NONE) {
        printf("write %x -> %s\n", addr, Fault[fault].name);         
        continue; 
      }
      printf("write %x -> %x\n", addr, phys);
    } else if (strstr(linep, "execute")) {
      sscanf(linep, "%s %x", temp, &addr);
      if ( (fault = linearToPhys(pl3e, addr, ACCESS_EXECUTE, &phys)) != FAULT_NONE) {
        printf("execute %x -> %s\n", addr, Fault[fault].name);         
        continue; 
      }
      printf("execute %x -> %x\n", addr, phys);

    } else {
      printf("illegal input %s\n", linep);
      break;
    }
  } // while

}
#endif

