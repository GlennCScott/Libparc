/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file parc_HashCodeTable.h
 * @ingroup datastructures
 *
 * A hashcode table requires the user to specify their own hash function
 * to operate on the object type being inserted.
 *
 * @author Marc Mosco, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef libparc_parc_HashCodeTable_h
#define libparc_parc_HashCodeTable_h

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <parc/algol/parc_HashCode.h>

struct parc_hashcode_table;
typedef struct parc_hashcode_table PARCHashCodeTable;

typedef PARCHashCode HashCodeType;


/**
 * @typedef PARCHashCodeTable_KeyEqualsFunc
 * @brief Are two keys equal?

 */

typedef bool (*PARCHashCodeTable_KeyEqualsFunc)(const void *keyA, const void *keyB);

/**
 * @typedef PARCHashCodeTable_HashCodeFunc
 */

typedef HashCodeType (*PARCHashCodeTable_HashCodeFunc)(const void *keyA);

/**
 * @typedef PARCHashCodeTable_Destroyer
 */

typedef void (*PARCHashCodeTable_Destroyer)(void **keyOrDataPtr);

/**
 * Create a Hash Table based on hash codes.
 *
 * @param [in] keyEqualsFunc Tests keys for equality.
 * @param [in] keyHashCodeFunc Returns the hash code of a key
 * @param [in] keyDestroyer  Called on Remove or Destroy to free stored keys, may be NULL.
 * @param [in] dataDestroyer Called on Remove or Destroy to free stored data, may be NULL.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCHashCodeTable *parcHashCodeTable_Create(PARCHashCodeTable_KeyEqualsFunc keyEqualsFunc,
                                            PARCHashCodeTable_HashCodeFunc keyHashCodeFunc,
                                            PARCHashCodeTable_Destroyer keyDestroyer,
                                            PARCHashCodeTable_Destroyer dataDestroyer);


/**
 * Create a Hash Table based on hash codes.
 *
 * @param [in] keyEqualsFunc   Tests keys for equality.
 * @param [in] keyHashCodeFunc Returns the hash code of a key
 * @param [in] keyDestroyer    Called on Remove or Destroy to free stored keys, may be NULL.
 * @param [in] dataDestroyer   Called on Remove or Destroy to free stored data, may be NULL.
 * @param [in] minimumSize     The minimum size of the table
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCHashCodeTable *parcHashCodeTable_Create_Size(PARCHashCodeTable_KeyEqualsFunc keyEqualsFunc,
                                                 PARCHashCodeTable_HashCodeFunc keyHashCodeFunc,
                                                 PARCHashCodeTable_Destroyer keyDestroyer,
                                                 PARCHashCodeTable_Destroyer dataDestroyer,
                                                 size_t minimumSize);

/**
 * Destroy the table and free all saved objects
 *
 * @param [in,out] tablePtr is a pointer to the `PARCHashCodeTable` reference.
 *
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void parcHashCodeTable_Destroy(PARCHashCodeTable **tablePtr);

/**
 * Add an element to the hash table.
 * @param [in,out] table  The key, must be usable with the {@link PARCHashCodeTable_KeyEqualsFunc} and {@link PARCHashCodeTable_HashCodeFunc}.
 * @param [in] key  The key, must be usable with the `keyEqualsFunc` and `keyHashCodeFunc`.
 * @param [in] data The value, must not be NULL
 *
 * @return true if key did not exist and data was added.  Returns false if key exists or error.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool parcHashCodeTable_Add(PARCHashCodeTable *table, void *key, void *data);

/**
 * Removes a key from an instance of `PARCHashCodeTable`, freeing key and data memory.  Does nothing if key does not
 * exist in the table.
 *
 * @param [in,out] table  The instance of `PARCHashCodeTable` from which the key will be removed.
 * @param [in] key  The key, must be usable with the {@link PARCHashCodeTable_KeyEqualsFunc} and {@link PARCHashCodeTable_HashCodeFunc}.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void parcHashCodeTable_Del(PARCHashCodeTable *table, const void *key);

/**
 * Returns the key value, or NULL if the key does not exist
 *
 * @param [in] table  The instance of `PARCHashCodeTable` from which the the value will be retrieved.
 * @param [in] key  The key to identify the desired value.
 *
 * @return A pointer to the value of the specified key.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void *parcHashCodeTable_Get(PARCHashCodeTable *table, const void *key);

/**
 * Returns the number of entries in the table
 *
 *
 * @param [in] table  The specified `PARCHashCodeTable` instance.
 * @return The number of entries in @p table.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
size_t parcHashCodeTable_Length(const PARCHashCodeTable *table);
#endif // libparc_parc_HashCodeTable_h
