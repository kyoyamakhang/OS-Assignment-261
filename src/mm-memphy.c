/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* Caitoa release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

// #ifdef MM_PAGING
/*
 * PAGING based Memory Management
 * Memory physical module mm/mm-memphy.c
 */

#include "mm.h"
#include "mm64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  MEMPHY_mv_csr - move MEMPHY cursor
 *  @mp: memphy struct
 *  @offset: offset
 */
int MEMPHY_mv_csr(struct memphy_struct *mp, addr_t offset)
{
   int numstep = 0;

   if (mp == NULL || mp->storage == NULL || mp->maxsz <= 0)
       return -1;

   mp->cursor = 0;
   while (numstep < offset && numstep < mp->maxsz)
   {
      /* Traverse sequentially */
      mp->cursor = (mp->cursor + 1) % mp->maxsz;
      numstep++;
   }

   return 0;
}

/*
 *  MEMPHY_seq_read - read MEMPHY device
 *  @mp: memphy struct
 *  @addr: address
 *  @value: obtained value
 */
int MEMPHY_seq_read(struct memphy_struct *mp, addr_t addr, BYTE *value)
{
   if (mp == NULL || mp->storage == NULL || value == NULL)
        return -1;

    if (mp->rdmflg)
        return -1;

    if (addr >= mp->maxsz)
        return -1;

    MEMPHY_mv_csr(mp, addr);
    *value = mp->storage[addr];

    return 0;
}

/*
 *  MEMPHY_read read MEMPHY device
 *  @mp: memphy struct
 *  @addr: address
 *  @value: obtained value
 */
int MEMPHY_read(struct memphy_struct *mp, addr_t addr, BYTE *value)
{
   if (mp == NULL || mp->storage == NULL || value == NULL)
        return -1;

    if (addr >= mp->maxsz)
        return -1;

    if (mp->rdmflg)
        *value = mp->storage[addr];
    else
        return MEMPHY_seq_read(mp, addr, value);

    return 0;
}

/*
 *  MEMPHY_seq_write - write MEMPHY device
 *  @mp: memphy struct
 *  @addr: address
 *  @data: written data
 */
int MEMPHY_seq_write(struct memphy_struct *mp, addr_t addr, BYTE value)
{

   if (mp == NULL || mp->storage == NULL)
        return -1;

    if (mp->rdmflg)
        return -1;

    if (addr >= mp->maxsz)
        return -1;

    MEMPHY_mv_csr(mp, addr);
    mp->storage[addr] = value;

    return 0;
}

/*
 *  MEMPHY_write-write MEMPHY device
 *  @mp: memphy struct
 *  @addr: address
 *  @data: written data
 */
int MEMPHY_write(struct memphy_struct *mp, addr_t addr, BYTE data)
{
   if (mp == NULL || mp->storage == NULL)
        return -1;

    if (addr >= mp->maxsz)
        return -1;

    if (mp->rdmflg)
        mp->storage[addr] = data;
    else
        return MEMPHY_seq_write(mp, addr, data);

    return 0;
}

/*
 *  MEMPHY_format-format MEMPHY device
 *  @mp: memphy struct
 */
int MEMPHY_format(struct memphy_struct *mp, int pagesz)
{
   int numfp;
    int iter;
    struct framephy_struct *newfst;

    if (mp == NULL || mp->maxsz <= 0 || pagesz <= 0)
        return -1;

    numfp = mp->maxsz / pagesz;

    if (numfp <= 0)
        return -1;

    mp->free_fp_list = NULL;
    mp->used_fp_list = NULL;

    for (iter = numfp - 1; iter >= 0; iter--)
    {
        newfst = malloc(sizeof(struct framephy_struct));

        if (newfst == NULL)
        {
            struct framephy_struct *temp;

            while (mp->free_fp_list != NULL)
            {
                temp = mp->free_fp_list;
                mp->free_fp_list = temp->fp_next;
                free(temp);
            }

            return -1;
        }

        newfst->fpn = iter;
        newfst->owner = NULL;
        newfst->fp_next = mp->free_fp_list;

        mp->free_fp_list = newfst;
    }

    return 0;
}

int MEMPHY_get_freefp(struct memphy_struct *mp, addr_t *retfpn)
{
    struct framephy_struct *fp;

    if (mp == NULL || retfpn == NULL)
        return -1;

    fp = mp->free_fp_list;

    if (fp == NULL)
        return -1;

    /* Remove frame from free list */
    mp->free_fp_list = fp->fp_next;

    /* Return frame number */
    *retfpn = fp->fpn;

    /* Move frame to used list */
    fp->fp_next = mp->used_fp_list;
    mp->used_fp_list = fp;

    return 0;
}

int MEMPHY_dump(struct memphy_struct *mp)
{
    /*
     * TODO dump memphy contnt mp->storage
     *     for tracing the memory content
     */

    int i;

    if (mp == NULL || mp->storage == NULL)
        return -1;

    printf("MEMPHY content:\n");

    for (i = 0; i < mp->maxsz; i++)
    {
        printf("%02X ", (unsigned char)mp->storage[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }

    printf("\n");

    return 0;
}

int MEMPHY_put_freefp(struct memphy_struct *mp, addr_t fpn)
{
    struct framephy_struct *fp;
    struct framephy_struct *prev = NULL;

    if (mp == NULL)
        return -1;

    /* Find frame in used list */
    fp = mp->used_fp_list;

    while (fp != NULL)
    {
        if (fp->fpn == fpn)
            break;

        prev = fp;
        fp = fp->fp_next;
    }

    /* Frame was not allocated */
    if (fp == NULL)
        return -1;

    /* Remove frame from used list */
    if (prev == NULL)
        mp->used_fp_list = fp->fp_next;
    else
        prev->fp_next = fp->fp_next;

    /* Return frame to free list */
    fp->fp_next = mp->free_fp_list;
    mp->free_fp_list = fp;

    fp->owner = NULL;

    return 0;
}

/*
 *  Init MEMPHY struct
 */
int init_memphy(struct memphy_struct *mp, addr_t max_size, int randomflg)
{
    if (mp == NULL)
        return -1;

    /* Initialize MEMPHY fields */
    mp->storage = NULL;
    mp->maxsz = 0;
    mp->rdmflg = (randomflg != 0) ? 1 : 0;
    mp->cursor = 0;
    mp->free_fp_list = NULL;
    mp->used_fp_list = NULL;

    /* Size 0 means this SWAP device is disabled */
    if (max_size == 0)
        return 0;

    /* maxsz is int, so prevent overflow */
    if (max_size > (addr_t)2147483647)
        return -1;

    mp->storage = (BYTE *)malloc(max_size * sizeof(BYTE));

    if (mp->storage == NULL)
        return -1;

    mp->maxsz = (int)max_size;

    memset(mp->storage, 0, max_size * sizeof(BYTE));

#ifdef MM64
    if (MEMPHY_format(mp, PAGING64_PAGESZ) != 0)
#else
    if (MEMPHY_format(mp, PAGING_PAGESZ) != 0)
#endif
    {
        free(mp->storage);
        mp->storage = NULL;
        mp->maxsz = 0;
        return -1;
    }

    return 0;
}

// #endif
