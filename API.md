# API Reference

## Header files

- [include/drip/det.h](#file-includedripdeth)
- [include/drip/format.h](#file-includedripformath)
- [include/drip/hash.h](#file-includedriphashh)
- [include/drip/link.h](#file-includedriplinkh)
- [include/drip/manifest.h](#file-includedripmanifesth)

## File include/drip/det.h





## Structures and Types

| Type | Name |
| ---: | :--- |
| enum  | [**drip\_det\_role\_t**](#enum-drip_det_role_t)  <br>_DET role determined from an HID._ |
| typedef uint8\_t | [**drip\_det\_t**](#typedef-drip_det_t)  <br>_16-byte DRIP Entity Tag (DET)._ |
| enum  | [**drip\_hhsi\_t**](#enum-drip_hhsi_t)  <br>_HHIT Suite ID (HHSI) values per RFC 9374._ |

## Functions

| Type | Name |
| ---: | :--- |
|  int | [**drip\_det\_decode**](#function-drip_det_decode) ([**drip\_det\_t**](#typedef-drip_det_t) \*det, const uint8\_t \*buffer, size\_t buffer\_size) <br>_Decode and validate a 16-byte buffer into a DET._ |
|  int | [**drip\_det\_encode**](#function-drip_det_encode) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det, uint8\_t \*buffer, size\_t buffer\_size) <br>_Encode a DET to its 16-byte wire format._ |
|  int | [**drip\_det\_from\_ipv6\_string**](#function-drip_det_from_ipv6_string) ([**drip\_det\_t**](#typedef-drip_det_t) \*det, const char \*string) <br>_Parse a canonical IPv6 address string into a DET._ |
|  const [**drip\_hash\_t**](#typedef-drip_hash_t) \* | [**drip\_det\_get\_hash**](#function-drip_det_get_hash) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br>_Get the hash of a DET._ |
|  uint16\_t | [**drip\_det\_get\_hda**](#function-drip_det_get_hda) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br>_Get the HHIT Domain Authority (HDA) of a DET._ |
|  uint8\_t | [**drip\_det\_get\_hhsi**](#function-drip_det_get_hhsi) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br>_Get the HHIT Suite ID (HHSI) of a DET._ |
|  uint32\_t | [**drip\_det\_get\_hid**](#function-drip_det_get_hid) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br>_Get the Hierarchy ID (HID) of a DET._ |
|  uint16\_t | [**drip\_det\_get\_raa**](#function-drip_det_get_raa) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br>_Get the Registered Assigning Authority (RAA) of a DET._ |
|  int | [**drip\_det\_init**](#function-drip_det_init) ([**drip\_det\_t**](#typedef-drip_det_t) \*det) <br>_Initialize a DET._ |
|  [**drip\_det\_role\_t**](#enum-drip_det_role_t) | [**drip\_det\_role**](#function-drip_det_role) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br>_Get the role of a DET from its HID._ |
|  int | [**drip\_det\_set\_hash**](#function-drip_det_set_hash) ([**drip\_det\_t**](#typedef-drip_det_t) \*det, const [**drip\_hash\_t**](#typedef-drip_hash_t) \*hash) <br>_Set the hash of a DET._ |
|  int | [**drip\_det\_set\_hda**](#function-drip_det_set_hda) ([**drip\_det\_t**](#typedef-drip_det_t) \*det, uint16\_t hda) <br>_Set the HHIT Domain Authority (HDA) of a DET._ |
|  int | [**drip\_det\_set\_hhsi**](#function-drip_det_set_hhsi) ([**drip\_det\_t**](#typedef-drip_det_t) \*det, [**drip\_hhsi\_t**](#enum-drip_hhsi_t) hhsi) <br>_Set the HHIT Suite ID (HHSI) of a DET._ |
|  int | [**drip\_det\_set\_hid**](#function-drip_det_set_hid) ([**drip\_det\_t**](#typedef-drip_det_t) \*det, uint32\_t hid) <br>_Set the Hierarchy ID (HID) of a DET._ |
|  int | [**drip\_det\_set\_raa**](#function-drip_det_set_raa) ([**drip\_det\_t**](#typedef-drip_det_t) \*det, uint16\_t raa) <br>_Set the Registered Assigning Authority (RAA) of a DET._ |
|  int | [**drip\_det\_to\_ipv6\_string**](#function-drip_det_to_ipv6_string) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det, char \*buffer, size\_t buffer\_size) <br>_Render a DET as a canonical IPv6 address string._ |
|  int | [**drip\_det\_update\_hash**](#function-drip_det_update_hash) ([**drip\_det\_t**](#typedef-drip_det_t) \*det, const [**drip\_hi\_t**](#typedef-drip_hi_t) \*hi, [**drip\_hash\_cb\_t**](#typedef-drip_hash_cb_t) callback, void \*context) <br>_Update the hash of a DET._ |
|  int | [**drip\_det\_validate**](#function-drip_det_validate) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br>_Validate the structural integrity of a DET._ |
|  int | [**drip\_det\_verify**](#function-drip_det_verify) (const [**drip\_det\_t**](#typedef-drip_det_t) \*det, const [**drip\_hi\_t**](#typedef-drip_hi_t) \*hi, [**drip\_hash\_cb\_t**](#typedef-drip_hash_cb_t) callback, void \*context) <br>_Verify the hash of a DET._ |
|  int | [**drip\_det\_verify\_delegation**](#function-drip_det_verify_delegation) (const [**drip\_det\_t**](#typedef-drip_det_t) \*parent, const [**drip\_det\_t**](#typedef-drip_det_t) \*child) <br>_Verify that a parent DET may delegate to a child DET._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DRIP\_DET\_CONTEXT\_ID\_SIZE**](#define-drip_det_context_id_size)  16<br>_Length of the hash customization string in bytes._ |
| define  | [**DRIP\_DET\_IPV6\_PREFIX\_STRING**](#define-drip_det_ipv6_prefix_string)  "2001:30::/28"<br>_DET IPv6 prefix string (2001:30::/28)._ |
| define  | [**DRIP\_DET\_IPV6\_STRING\_SIZE**](#define-drip_det_ipv6_string_size)  40<br>_Buffer size in bytes for a NULL terminated DET IPv6 string._ |
| define  | [**DRIP\_DET\_SIZE**](#define-drip_det_size)  16<br>_Size of a DET in bytes._ |

## Structures and Types Documentation

### enum `drip_det_role_t`

_DET role determined from an HID._
```c
enum drip_det_role_t {
    DRIP_DET_ROLE_UNKNOWN = 0,
    DRIP_DET_ROLE_APEX = 1,
    DRIP_DET_ROLE_RAA = 2,
    DRIP_DET_ROLE_HDA = 3
};
```


HID cannot distinguish HDA from UA so both map to DRIP\_DET\_ROLE\_HDA.



**See also:** [https://www.rfc-editor.org/rfc/rfc9886.html#section-3](https://www.rfc-editor.org/rfc/rfc9886.html#section-3)
### typedef `drip_det_t`

_16-byte DRIP Entity Tag (DET)._
```c
typedef uint8_t drip_det_t[16];
```


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3](https://www.rfc-editor.org/rfc/rfc9374.html#section-3)
### enum `drip_hhsi_t`

_HHIT Suite ID (HHSI) values per RFC 9374._
```c
enum drip_hhsi_t {
    DRIP_HHSI_RESERVED = 0,
    DRIP_HHSI_RSA_DSA_SHA256 = 1,
    DRIP_HHSI_ECDSA_SHA384 = 2,
    DRIP_HHSI_ECDSA_LOW_SHA1 = 3,
    DRIP_HHSI_EDDSA_CSHAKE128 = 5,
    DRIP_HHSI_HDA_PRIVATE_USE_1 = 254,
    DRIP_HHSI_HDA_PRIVATE_USE_2 = 255
};
```


Identifies the hash and signature algorithms used by a DET.



**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2)

## Functions Documentation

### function `drip_det_decode`

_Decode and validate a 16-byte buffer into a DET._
```c
int drip_det_decode (
    drip_det_t *det,
    const uint8_t *buffer,
    size_t buffer_size
) 
```


You could also just use `memcpy()` but using this future proofs your code in case the internal representation ever changes.



**Parameters:**


* `det` Pointer to the DET that receives the decoded bytes. 
* `buffer` Input buffer holding the wire format bytes. 
* `buffer_size` Size of buffer in bytes. Must be at least DRIP\_DET\_SIZE.


**Return value:**


* `DRIP_SUCCESS` on success. 
* `DRIP_ERROR_NULL_POINTER` if det or buffer is NULL. 
* `DRIP_ERROR_BUFFER_TOO_SMALL` if buffer\_size is less than DRIP\_DET\_SIZE. 
* `DRIP_ERROR_INVALID_IPV6_PREFIX` if the decoded prefix is not 2001:30::/28.


**See also:** [**drip\_det\_validate**](#function-drip_det_validate)
### function `drip_det_encode`

_Encode a DET to its 16-byte wire format._
```c
int drip_det_encode (
    const drip_det_t *det,
    uint8_t *buffer,
    size_t buffer_size
) 
```


You could also just use `memcpy()` but using this future proofs your code in case the internal representation ever changes.



**Parameters:**


* `det` Pointer to the DET to encode. 
* `buffer` Output buffer for the wire format bytes. 
* `buffer_size` Size of buffer in bytes. Must be at least DRIP\_DET\_SIZE.


**Return value:**


* `DRIP_SUCCESS` on success. 
* `DRIP_ERROR_NULL_POINTER` if det or buffer is NULL. 
* `DRIP_ERROR_BUFFER_TOO_SMALL` if buffer\_size is less than DRIP\_DET\_SIZE.
### function `drip_det_from_ipv6_string`

_Parse a canonical IPv6 address string into a DET._
```c
int drip_det_from_ipv6_string (
    drip_det_t *det,
    const char *string
) 
```


**Parameters:**


* `det` Pointer to the DET that receives the parsed bytes. 
* `string` NULL terminated ipv6 string.


**Return value:**


* `DRIP_SUCCESS` if the string parsed and is a structurally valid DET. 
* `DRIP_ERROR_NULL_POINTER` if det or string is NULL. 
* `DRIP_ERROR_INVALID_IPV6_STRING` if string is not a valid ipv6 address. 
* `DRIP_ERROR_INVALID_IPV6_PREFIX` if the prefix is outside 2001:30::/28.
### function `drip_det_get_hash`

_Get the hash of a DET._
```c
const drip_hash_t * drip_det_get_hash (
    const drip_det_t *det
) 
```


**Parameters:**


* `det` Pointer to the DET.


**Returns:**

Pointer to the stored hash or NULL if det is NULL.
### function `drip_det_get_hda`

_Get the HHIT Domain Authority (HDA) of a DET._
```c
uint16_t drip_det_get_hda (
    const drip_det_t *det
) 
```


**Parameters:**


* `det` Pointer to the DET.


**Returns:**

The stored HDA or 0 if det is NULL.



**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3.2](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3.2)
### function `drip_det_get_hhsi`

_Get the HHIT Suite ID (HHSI) of a DET._
```c
uint8_t drip_det_get_hhsi (
    const drip_det_t *det
) 
```


**Parameters:**


* `det` Pointer to the DET.


**Returns:**

The stored HHSI or 0 if det is NULL.



**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2)
### function `drip_det_get_hid`

_Get the Hierarchy ID (HID) of a DET._
```c
uint32_t drip_det_get_hid (
    const drip_det_t *det
) 
```


**Parameters:**


* `det` Pointer to the DET.


**Returns:**

The stored HID or 0 if det is NULL.



**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3)
### function `drip_det_get_raa`

_Get the Registered Assigning Authority (RAA) of a DET._
```c
uint16_t drip_det_get_raa (
    const drip_det_t *det
) 
```


**Parameters:**


* `det` Pointer to the DET.


**Returns:**

The stored RAA or 0 if det is NULL.



**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3.1](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3.1)
### function `drip_det_init`

_Initialize a DET._
```c
int drip_det_init (
    drip_det_t *det
) 
```


Zeroes the DET and sets the IPv6 prefix to 2001:30::/28.



**Parameters:**


* `det` Pointer to the DET to initialize.


**Return value:**


* `DRIP_SUCCESS` if the DET was initialized. 
* `DRIP_ERROR_NULL_POINTER` if det is NULL.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.1](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.1)
### function `drip_det_role`

_Get the role of a DET from its HID._
```c
drip_det_role_t drip_det_role (
    const drip_det_t *det
) 
```


Apex is an RAA 0-3 with a reserved HDA (0, 4096, 8192 or 12288). Any other reserved HDA is an RAA. Any other HID is either HDA or UA.



**Parameters:**


* `det` Pointer to the DET.


**Returns:**

The determined role or DRIP\_DET\_ROLE\_UNKNOWN if det is NULL.



**See also:** [https://www.rfc-editor.org/rfc/rfc9886.html#section-3](https://www.rfc-editor.org/rfc/rfc9886.html#section-3)
### function `drip_det_set_hash`

_Set the hash of a DET._
```c
int drip_det_set_hash (
    drip_det_t *det,
    const drip_hash_t *hash
) 
```


Use this only if hash comes from an external source. Normally you should use `drip_det_update_hash()` instead.



**Parameters:**


* `det` Pointer to the DET to modify. 
* `hash` Pointer to the hash to store.


**Return value:**


* `DRIP_SUCCESS` if the hash was stored. 
* `DRIP_ERROR_NULL_POINTER` if det or hash is NULL.
### function `drip_det_set_hda`

_Set the HHIT Domain Authority (HDA) of a DET._
```c
int drip_det_set_hda (
    drip_det_t *det,
    uint16_t hda
) 
```


This is a 14 bit value. Values greater than 0x3FFF are out of range.



**Parameters:**


* `det` Pointer to the DET to modify. 
* `hda` HHIT Domain Authority to store.


**Return value:**


* `DRIP_SUCCESS` if the HDA was stored. 
* `DRIP_ERROR_NULL_POINTER` if det is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if hda &gt; 0x3FFF.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3.2](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3.2)
### function `drip_det_set_hhsi`

_Set the HHIT Suite ID (HHSI) of a DET._
```c
int drip_det_set_hhsi (
    drip_det_t *det,
    drip_hhsi_t hhsi
) 
```


**Parameters:**


* `det` Pointer to the DET to modify. 
* `hhsi` HHIT Suite ID to store.


**Return value:**


* `DRIP_SUCCESS` if the HHSI was stored. 
* `DRIP_ERROR_NULL_POINTER` if det is NULL.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2)
### function `drip_det_set_hid`

_Set the Hierarchy ID (HID) of a DET._
```c
int drip_det_set_hid (
    drip_det_t *det,
    uint32_t hid
) 
```


This is a 28 bit value. Values greater than 0x0FFFFFFF are out of range.



**Parameters:**


* `det` Pointer to the DET to modify. 
* `hid` Hierarchy ID to store.


**Return value:**


* `DRIP_SUCCESS` if the HID was stored. 
* `DRIP_ERROR_NULL_POINTER` if det is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if hid &gt; 0x0FFFFFFF.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3)
### function `drip_det_set_raa`

_Set the Registered Assigning Authority (RAA) of a DET._
```c
int drip_det_set_raa (
    drip_det_t *det,
    uint16_t raa
) 
```


This is a 14 bit value. Values greater than 0x3FFF are out of range.



**Parameters:**


* `det` Pointer to the DET to modify. 
* `raa` Registered Assigning Authority to store.


**Return value:**


* `DRIP_SUCCESS` if the RAA was stored. 
* `DRIP_ERROR_NULL_POINTER` if det is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if raa &gt; 0x3FFF.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3.1](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3.1)
### function `drip_det_to_ipv6_string`

_Render a DET as a canonical IPv6 address string._
```c
int drip_det_to_ipv6_string (
    const drip_det_t *det,
    char *buffer,
    size_t buffer_size
) 
```


**Parameters:**


* `det` Pointer to the DET to render. 
* `buffer` Output buffer for the NULL terminated ipv6 string. 
* `buffer_size` Size of the output buffer.


**Return value:**


* `DRIP_SUCCESS` if the DET was rendered. 
* `DRIP_ERROR_NULL_POINTER` if det or buffer is NULL. 
* `DRIP_ERROR_BUFFER_TOO_SMALL` if buffer\_size is too small to hold the rendered ipv6 string.
### function `drip_det_update_hash`

_Update the hash of a DET._
```c
int drip_det_update_hash (
    drip_det_t *det,
    const drip_hi_t *hi,
    drip_hash_cb_t callback,
    void *context
) 
```


Hashes the first 8 bytes of the DET concatenated with the Host Identity (HI) using the caller supplied callback.



**Parameters:**


* `det` Pointer to the DET to modify. 
* `hi` Pointer to the Host Identity. 
* `callback` Callback function used to generate the hash. 
* `context` Opaque context passed to the callback.


**Precondition:**

You must call [**drip\_det\_set\_hid()**](#function-drip_det_set_hid) and[**drip\_det\_set\_hhsi()**](#function-drip_det_set_hhsi) before calling this function.



**Return value:**


* `DRIP_SUCCESS` if the hash was stored. 
* `DRIP_ERROR_NULL_POINTER` if det or hi or callback is NULL. 
* `DRIP_ERROR_CALLBACK_FAILED` if callback returned an error. 
* `DRIP_ERROR_INVALID_LENGTH` if resulting hash size does not match DRIP\_HASH\_SIZE.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.5.2](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.5.2)
### function `drip_det_validate`

_Validate the structural integrity of a DET._
```c
int drip_det_validate (
    const drip_det_t *det
) 
```


Checks the IPv6 prefix. Does not verify the ORCHID hash, use [**drip\_det\_verify()**](#function-drip_det_verify) for that. Reserved values are considered valid.



**Parameters:**


* `det` Pointer to the DET to validate.


**Return value:**


* `DRIP_SUCCESS` if det is structurally valid. 
* `DRIP_ERROR_NULL_POINTER` if det is NULL. 
* `DRIP_ERROR_INVALID_IPV6_PREFIX` if bytes 0-3 do not match the 2001:30::/28 prefix.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.1](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.1)

**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.2)

**See also:** [https://www.iana.org/assignments/drip/drip.xhtml#drip-raa](https://www.iana.org/assignments/drip/drip.xhtml#drip-raa)

**See also:** [https://www.rfc-editor.org/rfc/rfc9886.html](https://www.rfc-editor.org/rfc/rfc9886.html)
### function `drip_det_verify`

_Verify the hash of a DET._
```c
int drip_det_verify (
    const drip_det_t *det,
    const drip_hi_t *hi,
    drip_hash_cb_t callback,
    void *context
) 
```


Hashes the first 8 bytes of the DET concatenated with the Host Identity (HI) using the caller supplied callback and compares the result to the stored hash.



**Parameters:**


* `det` Pointer to the DET to verify. 
* `hi` Pointer to the Host Identity. 
* `callback` Callback function used to generate the hash. 
* `context` Opaque context passed to the callback.


**Return value:**


* `DRIP_SUCCESS` if the hash matches. 
* `DRIP_ERROR_NULL_POINTER` if det or hi or callback is NULL. 
* `DRIP_ERROR_CALLBACK_FAILED` if callback returned non-zero. 
* `DRIP_ERROR_INVALID_LENGTH` if resulting hash size does not match DRIP\_HASH\_SIZE. 
* `DRIP_ERROR_VERIFICATION_FAILED` if the hash does not match.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.5.2](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.5.2)
### function `drip_det_verify_delegation`

_Verify that a parent DET may delegate to a child DET._
```c
int drip_det_verify_delegation (
    const drip_det_t *parent,
    const drip_det_t *child
) 
```


Uses Hierarchy ID (HID) only. HID is divided into Registered Assigning Authority (RAA) and HHIT Domain Authority (HDA). Does not verify hashes or signatures.

Apex may only delegate to an RAA. RAA may only delegate to an HDA with the same RAA. HDA may only delegate to an HDA with the same RAA and HDA. UA is considered to be an HDA.



**Parameters:**


* `parent` Pointer to the parent DET. 
* `child` Pointer to the child DET.


**Return value:**


* `DRIP_SUCCESS` if the delegation is valid. 
* `DRIP_ERROR_NULL_POINTER` if parent or child is NULL. 
* `DRIP_ERROR_INVALID_APEX_DELEGATION` if parent is Apex and child is not an RAA. 
* `DRIP_ERROR_INVALID_RAA_DELEGATION` if parent is RAA and child is not an HDA with the same RAA. 
* `DRIP_ERROR_INVALID_HDA_DELEGATION` if parent is HDA and child is not an HDA with the same RAA and HDA.


**See also:** [https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3](https://www.rfc-editor.org/rfc/rfc9374.html#section-3.3)

**See also:** [https://www.rfc-editor.org/rfc/rfc9886.html#section-3](https://www.rfc-editor.org/rfc/rfc9886.html#section-3)

## Macros Documentation

### define `DRIP_DET_CONTEXT_ID_SIZE`

_Length of the hash customization string in bytes._
```c
#define DRIP_DET_CONTEXT_ID_SIZE 16
```

### define `DRIP_DET_IPV6_PREFIX_STRING`

_DET IPv6 prefix string (2001:30::/28)._
```c
#define DRIP_DET_IPV6_PREFIX_STRING "2001:30::/28"
```

### define `DRIP_DET_IPV6_STRING_SIZE`

_Buffer size in bytes for a NULL terminated DET IPv6 string._
```c
#define DRIP_DET_IPV6_STRING_SIZE 40
```

### define `DRIP_DET_SIZE`

_Size of a DET in bytes._
```c
#define DRIP_DET_SIZE 16
```


## File include/drip/format.h





## Structures and Types

| Type | Name |
| ---: | :--- |
| typedef uint8\_t | [**drip\_hi\_t**](#typedef-drip_hi_t)  <br> |
| enum  | [**drip\_sam\_type\_t**](#enum-drip_sam_type_t)  <br> |
| typedef uint8\_t | [**drip\_signature\_t**](#typedef-drip_signature_t)  <br> |
| enum  | [**drip\_status\_t**](#enum-drip_status_t)  <br> |


## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DRIP\_HI\_SIZE**](#define-drip_hi_size)  32<br> |
| define  | [**DRIP\_SIGNATURE\_SIZE**](#define-drip_signature_size)  64<br> |
| define  | [**DRIP\_TIMESTAMP\_EPOCH**](#define-drip_timestamp_epoch)  1546300800<br>_Timestamp epoch (2019-01-01 00:00:00 UTC as Unix timestamp)._ |

## Structures and Types Documentation

### typedef `drip_hi_t`

```c
typedef uint8_t drip_hi_t[32];
```

### enum `drip_sam_type_t`

```c
enum drip_sam_type_t {
    DRIP_SAM_TYPE_LINK = 0x01,
    DRIP_SAM_TYPE_WRAPPER = 0x02,
    DRIP_SAM_TYPE_MANIFEST = 0x03,
    DRIP_SAM_TYPE_FRAME = 0x04
};
```

### typedef `drip_signature_t`

```c
typedef uint8_t drip_signature_t[64];
```

### enum `drip_status_t`

```c
enum drip_status_t {
    DRIP_SUCCESS = 0,
    DRIP_ERROR_NULL_POINTER = -1,
    DRIP_ERROR_BUFFER_TOO_SMALL = -2,
    DRIP_ERROR_BUFFER_TOO_LARGE = -3,
    DRIP_ERROR_ARRAY_OVERFLOW = -4,
    DRIP_ERROR_INVALID_INDEX = -5,
    DRIP_ERROR_CALLBACK_FAILED = -6,
    DRIP_ERROR_INVALID_LENGTH = -7,
    DRIP_ERROR_INVALID_SAM_TYPE = -8,
    DRIP_ERROR_OUT_OF_RANGE = -9,
    DRIP_ERROR_INVALID_IPV6_PREFIX = -10,
    DRIP_ERROR_VERIFICATION_FAILED = -11,
    DRIP_ERROR_INVALID_TIMESTAMP = -12,
    DRIP_ERROR_INVALID_CHILD_DET = -13,
    DRIP_ERROR_INVALID_PARENT_DET = -14,
    DRIP_ERROR_INVALID_IPV6_STRING = -16,
    DRIP_ERROR_INVALID_DET = -18,
    DRIP_ERROR_TIMESTAMP_NOT_YET_VALID = -19,
    DRIP_ERROR_TIMESTAMP_EXPIRED = -20,
    DRIP_ERROR_INVALID_APEX_DELEGATION = -21,
    DRIP_ERROR_INVALID_RAA_DELEGATION = -22,
    DRIP_ERROR_INVALID_HDA_DELEGATION = -23
};
```



## Macros Documentation

### define `DRIP_HI_SIZE`

```c
#define DRIP_HI_SIZE 32
```

### define `DRIP_SIGNATURE_SIZE`

```c
#define DRIP_SIGNATURE_SIZE 64
```

### define `DRIP_TIMESTAMP_EPOCH`

_Timestamp epoch (2019-01-01 00:00:00 UTC as Unix timestamp)._
```c
#define DRIP_TIMESTAMP_EPOCH 1546300800
```


## File include/drip/hash.h





## Structures and Types

| Type | Name |
| ---: | :--- |
| typedef int(\* | [**drip\_hash\_cb\_t**](#typedef-drip_hash_cb_t)  <br>_Callback function type for producing hashes._ |
| typedef uint8\_t | [**drip\_hash\_t**](#typedef-drip_hash_t)  <br> |

## Functions

| Type | Name |
| ---: | :--- |
|  int | [**drip\_hash**](#function-drip_hash) (const uint8\_t \*input, size\_t input\_length, const uint8\_t \*customization, size\_t customization\_length, [**drip\_hash\_t**](#typedef-drip_hash_t) \*hash, [**drip\_hash\_cb\_t**](#typedef-drip_hash_cb_t) callback, void \*context) <br>_Hash input using a caller supplied callback._ |
|  int | [**drip\_hash\_to\_hex**](#function-drip_hash_to_hex) (const [**drip\_hash\_t**](#typedef-drip_hash_t) \*hash, char \*hex, size\_t hex\_size) <br> |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DRIP\_HASH\_SIZE**](#define-drip_hash_size)  8<br> |

## Structures and Types Documentation

### typedef `drip_hash_cb_t`

_Callback function type for producing hashes._
```c
typedef int(* drip_hash_cb_t) (void *context, const uint8_t *input, size_t input_length, const uint8_t *customization, size_t customization_length, uint8_t *buffer, size_t buffer_size, size_t *output_length);
```


Called by [**drip\_hash()**](#function-drip_hash) to perform the actual hashing of the payload.



**Parameters:**


* `context` Opaque context passed to the callback. 
* `input` Pointer to the payload to hash. 
* `input_length` Length of the payload in bytes. 
* `customization` Pointer to the hash customization string or NULL. 
* `customization_length` Length of the customization string in bytes. 
* `buffer` Output buffer for the hash. 
* `buffer_size` Size of the hash buffer in bytes. 
* `output_length` Receives resulting hash length written.


**Return value:**


* `0` on success. 
* `Non-zero` on hashing failure.
### typedef `drip_hash_t`

```c
typedef uint8_t drip_hash_t[8];
```


## Functions Documentation

### function `drip_hash`

_Hash input using a caller supplied callback._
```c
int drip_hash (
    const uint8_t *input,
    size_t input_length,
    const uint8_t *customization,
    size_t customization_length,
    drip_hash_t *hash,
    drip_hash_cb_t callback,
    void *context
) 
```


**Parameters:**


* `input` Pointer to the payload to hash. 
* `input_length` Length of the payload in bytes. 
* `customization` Pointer to the hash customization string or NULL. 
* `customization_length` Length of the customization string in bytes. 
* `hash` Output buffer for the hash. 
* `callback` Callback function used to generate the hash. 
* `context` Opaque context passed to the callback.


**Return value:**


* `DRIP_SUCCESS` if the hash was generated. 
* `DRIP_ERROR_NULL_POINTER` if input or hash or callback is NULL or if customization is NULL with customization\_length &gt; 0. 
* `DRIP_ERROR_CALLBACK_FAILED` if callback returned an error. 
* `DRIP_ERROR_INVALID_LENGTH` if resulting hash size does not match DRIP\_HASH\_SIZE.
### function `drip_hash_to_hex`

```c
int drip_hash_to_hex (
    const drip_hash_t *hash,
    char *hex,
    size_t hex_size
) 
```


## Macros Documentation

### define `DRIP_HASH_SIZE`

```c
#define DRIP_HASH_SIZE 8
```


## File include/drip/link.h





## Structures and Types

| Type | Name |
| ---: | :--- |
| typedef int(\* | [**drip\_link\_sign\_cb\_t**](#typedef-drip_link_sign_cb_t)  <br>_Callback function type for producing link signatures._ |
| struct | [**drip\_link\_t**](#struct-drip_link_t) <br> |
| typedef int(\* | [**drip\_link\_verify\_cb\_t**](#typedef-drip_link_verify_cb_t)  <br>_Callback function type for verifying link signatures._ |

## Functions

| Type | Name |
| ---: | :--- |
|  int | [**drip\_link\_decode**](#function-drip_link_decode) ([**drip\_link\_t**](#struct-drip_link_t) \*link, const uint8\_t \*buffer, size\_t buffer\_size) <br> |
|  int | [**drip\_link\_encode**](#function-drip_link_encode) (const [**drip\_link\_t**](#struct-drip_link_t) \*link, uint8\_t \*buffer, size\_t buffer\_size, size\_t \*encoded\_length) <br> |
|  const [**drip\_det\_t**](#typedef-drip_det_t) \* | [**drip\_link\_get\_child\_det**](#function-drip_link_get_child_det) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br> |
|  const [**drip\_hi\_t**](#typedef-drip_hi_t) \* | [**drip\_link\_get\_child\_hi**](#function-drip_link_get_child_hi) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br> |
|  const [**drip\_det\_t**](#typedef-drip_det_t) \* | [**drip\_link\_get\_parent\_det**](#function-drip_link_get_parent_det) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br> |
|  const [**drip\_signature\_t**](#typedef-drip_signature_t) \* | [**drip\_link\_get\_signature**](#function-drip_link_get_signature) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br> |
|  uint32\_t | [**drip\_link\_get\_vna**](#function-drip_link_get_vna) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br>_Get the vna timestamp._ |
|  uint32\_t | [**drip\_link\_get\_vna\_unixtime**](#function-drip_link_get_vna_unixtime) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br>_Get the vna as a unix timestamp._ |
|  uint32\_t | [**drip\_link\_get\_vnb**](#function-drip_link_get_vnb) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br>_Get the vnb timestamp._ |
|  uint32\_t | [**drip\_link\_get\_vnb\_unixtime**](#function-drip_link_get_vnb_unixtime) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br>_Get the vnb as a unix timestamp._ |
|  int | [**drip\_link\_init**](#function-drip_link_init) ([**drip\_link\_t**](#struct-drip_link_t) \*link) <br> |
|  int | [**drip\_link\_set\_child\_det**](#function-drip_link_set_child_det) ([**drip\_link\_t**](#struct-drip_link_t) \*link, const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br> |
|  int | [**drip\_link\_set\_child\_hi**](#function-drip_link_set_child_hi) ([**drip\_link\_t**](#struct-drip_link_t) \*link, const [**drip\_hi\_t**](#typedef-drip_hi_t) \*hi) <br> |
|  int | [**drip\_link\_set\_parent\_det**](#function-drip_link_set_parent_det) ([**drip\_link\_t**](#struct-drip_link_t) \*link, const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br> |
|  int | [**drip\_link\_set\_signature**](#function-drip_link_set_signature) ([**drip\_link\_t**](#struct-drip_link_t) \*link, const [**drip\_signature\_t**](#typedef-drip_signature_t) \*signature) <br> |
|  int | [**drip\_link\_set\_vna**](#function-drip_link_set_vna) ([**drip\_link\_t**](#struct-drip_link_t) \*link, uint32\_t vna) <br>_Set the vna timestamp._ |
|  int | [**drip\_link\_set\_vna\_unixtime**](#function-drip_link_set_vna_unixtime) ([**drip\_link\_t**](#struct-drip_link_t) \*link, uint32\_t unixtime) <br>_Set the vna from unix timestamp._ |
|  int | [**drip\_link\_set\_vnb**](#function-drip_link_set_vnb) ([**drip\_link\_t**](#struct-drip_link_t) \*link, uint32\_t vnb) <br>_Set the vnb timestamp._ |
|  int | [**drip\_link\_set\_vnb\_unixtime**](#function-drip_link_set_vnb_unixtime) ([**drip\_link\_t**](#struct-drip_link_t) \*link, uint32\_t unixtime) <br>_Set the vnb from unix timestamp._ |
|  int | [**drip\_link\_sign**](#function-drip_link_sign) ([**drip\_link\_t**](#struct-drip_link_t) \*link, [**drip\_link\_sign\_cb\_t**](#typedef-drip_link_sign_cb_t) callback, void \*context) <br>_Sign a DRIP Link._ |
|  int | [**drip\_link\_to\_json**](#function-drip_link_to_json) (const [**drip\_link\_t**](#struct-drip_link_t) \*link, char \*buffer, size\_t buffer\_size, size\_t \*json\_length) <br>_Serialize a DRIP link to a JSON string._ |
|  int | [**drip\_link\_validate**](#function-drip_link_validate) (const [**drip\_link\_t**](#struct-drip_link_t) \*link) <br>_Validate the structural state of a DRIP Link._ |
|  int | [**drip\_link\_verify**](#function-drip_link_verify) (const [**drip\_link\_t**](#struct-drip_link_t) \*link, uint32\_t unixtime, [**drip\_link\_verify\_cb\_t**](#typedef-drip_link_verify_cb_t) callback, void \*context) <br>_Verify the signature of a DRIP Link._ |
|  int | [**drip\_link\_verify\_chain**](#function-drip_link_verify_chain) (const [**drip\_link\_t**](#struct-drip_link_t) \*link\_array, size\_t link\_count, const [**drip\_det\_t**](#typedef-drip_det_t) \*root\_det, const [**drip\_hi\_t**](#typedef-drip_hi_t) \*root\_hi, uint32\_t unixtime, [**drip\_hash\_cb\_t**](#typedef-drip_hash_cb_t) hash\_cb, [**drip\_link\_verify\_cb\_t**](#typedef-drip_link_verify_cb_t) verify\_cb) <br>_Verify a chain of DRIP Links from a trusted root._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DRIP\_LINK\_SIZE**](#define-drip_link_size)  137<br> |

## Structures and Types Documentation

### typedef `drip_link_sign_cb_t`

_Callback function type for producing link signatures._
```c
typedef int(* drip_link_sign_cb_t) (void *context, const uint8_t *input, size_t input_length, uint8_t *buffer, size_t buffer_size, size_t *output_length);
```


Called by [**drip\_link\_sign()**](#function-drip_link_sign) to perform the actual signing of the payload.



**Parameters:**


* `context` Opaque context passed to the callback. 
* `input` Pointer to the payload to sign. 
* `input_length` Length of the payload in bytes. 
* `buffer` Output buffer for the signature. 
* `buffer_size` Size of the signature buffer in bytes. 
* `output_length` Receives resulting signature length written.


**Return value:**


* `0` on success. 
* `Non-zero` on signing failure.
### struct `drip_link_t`


Variables:

-  [**drip\_det\_t**](#typedef-drip_det_t) child_det  

-  [**drip\_hi\_t**](#typedef-drip_hi_t) child_hi  

-  [**drip\_det\_t**](#typedef-drip_det_t) parent_det  

-  uint8\_t sam_type  

-  [**drip\_signature\_t**](#typedef-drip_signature_t) signature  

-  uint32\_t vna  

-  uint32\_t vnb  

### typedef `drip_link_verify_cb_t`

_Callback function type for verifying link signatures._
```c
typedef int(* drip_link_verify_cb_t) (void *context, const uint8_t *input, size_t input_length, const uint8_t *signature, size_t signature_length);
```


Called by [**drip\_link\_verify()**](#function-drip_link_verify) to perform the actual verification of the signed payload.



**Parameters:**


* `context` Opaque context passed to the callback. 
* `input` Pointer to the signed payload data. 
* `input_length` Length of the signed payload in bytes. 
* `signature` Pointer to the signature to verify against. 
* `signature_length` Length of the signature in bytes.


**Return value:**


* `0` on success. 
* `Non-zero` on verification failure.

## Functions Documentation

### function `drip_link_decode`

```c
int drip_link_decode (
    drip_link_t *link,
    const uint8_t *buffer,
    size_t buffer_size
) 
```

### function `drip_link_encode`

```c
int drip_link_encode (
    const drip_link_t *link,
    uint8_t *buffer,
    size_t buffer_size,
    size_t *encoded_length
) 
```

### function `drip_link_get_child_det`

```c
const drip_det_t * drip_link_get_child_det (
    const drip_link_t *link
) 
```

### function `drip_link_get_child_hi`

```c
const drip_hi_t * drip_link_get_child_hi (
    const drip_link_t *link
) 
```

### function `drip_link_get_parent_det`

```c
const drip_det_t * drip_link_get_parent_det (
    const drip_link_t *link
) 
```

### function `drip_link_get_signature`

```c
const drip_signature_t * drip_link_get_signature (
    const drip_link_t *link
) 
```

### function `drip_link_get_vna`

_Get the vna timestamp._
```c
uint32_t drip_link_get_vna (
    const drip_link_t *link
) 
```


Returned as seconds since DRIP\_TIMESTAMP\_EPOCH.



**Parameters:**


* `link` Pointer to the link.


**Returns:**

The stored vna, or 0 if link is NULL.
### function `drip_link_get_vna_unixtime`

_Get the vna as a unix timestamp._
```c
uint32_t drip_link_get_vna_unixtime (
    const drip_link_t *link
) 
```


**Parameters:**


* `link` Pointer to the link.


**Returns:**

The vna as unix timestamp or 0 if link is NULL.
### function `drip_link_get_vnb`

_Get the vnb timestamp._
```c
uint32_t drip_link_get_vnb (
    const drip_link_t *link
) 
```


Returned as seconds since DRIP\_TIMESTAMP\_EPOCH.



**Parameters:**


* `link` Pointer to the link.


**Returns:**

The stored vnb, or 0 if link is NULL.
### function `drip_link_get_vnb_unixtime`

_Get the vnb as a unix timestamp._
```c
uint32_t drip_link_get_vnb_unixtime (
    const drip_link_t *link
) 
```


**Parameters:**


* `link` Pointer to the link.


**Returns:**

The vnb as unix timestamp or 0 if link is NULL.
### function `drip_link_init`

```c
int drip_link_init (
    drip_link_t *link
) 
```

### function `drip_link_set_child_det`

```c
int drip_link_set_child_det (
    drip_link_t *link,
    const drip_det_t *det
) 
```

### function `drip_link_set_child_hi`

```c
int drip_link_set_child_hi (
    drip_link_t *link,
    const drip_hi_t *hi
) 
```

### function `drip_link_set_parent_det`

```c
int drip_link_set_parent_det (
    drip_link_t *link,
    const drip_det_t *det
) 
```

### function `drip_link_set_signature`

```c
int drip_link_set_signature (
    drip_link_t *link,
    const drip_signature_t *signature
) 
```

### function `drip_link_set_vna`

_Set the vna timestamp._
```c
int drip_link_set_vna (
    drip_link_t *link,
    uint32_t vna
) 
```


Stored internally as seconds since DRIP\_TIMESTAMP\_EPOCH.



**Parameters:**


* `link` Pointer to the link to modify. 
* `vna` Offset from DRIP\_TIMESTAMP\_EPOCH in seconds.


**Return value:**


* `DRIP_SUCCESS` if vna was stored. 
* `DRIP_ERROR_NULL_POINTER` if link is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if vna &gt; UINT32\_MAX - DRIP\_TIMESTAMP\_EPOCH.
### function `drip_link_set_vna_unixtime`

_Set the vna from unix timestamp._
```c
int drip_link_set_vna_unixtime (
    drip_link_t *link,
    uint32_t unixtime
) 
```


**Parameters:**


* `link` Pointer to the link to modify. 
* `unixtime` Unix timestamp in seconds.


**Return value:**


* `DRIP_SUCCESS` if vna was stored. 
* `DRIP_ERROR_NULL_POINTER` if link is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if unixtime &lt; DRIP\_TIMESTAMP\_EPOCH.
### function `drip_link_set_vnb`

_Set the vnb timestamp._
```c
int drip_link_set_vnb (
    drip_link_t *link,
    uint32_t vnb
) 
```


Stored internally as seconds since DRIP\_TIMESTAMP\_EPOCH.



**Parameters:**


* `link` Pointer to the link to modify. 
* `vnb` Offset from DRIP\_TIMESTAMP\_EPOCH in seconds.


**Return value:**


* `DRIP_SUCCESS` if vnb was stored. 
* `DRIP_ERROR_NULL_POINTER` if link is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if vnb &gt; UINT32\_MAX - DRIP\_TIMESTAMP\_EPOCH.
### function `drip_link_set_vnb_unixtime`

_Set the vnb from unix timestamp._
```c
int drip_link_set_vnb_unixtime (
    drip_link_t *link,
    uint32_t unixtime
) 
```


**Parameters:**


* `link` Pointer to the link to modify. 
* `unixtime` Unix timestamp in seconds.


**Return value:**


* `DRIP_SUCCESS` if vnb was stored. 
* `DRIP_ERROR_NULL_POINTER` if link is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if unixtime &lt; DRIP\_TIMESTAMP\_EPOCH.
### function `drip_link_sign`

_Sign a DRIP Link._
```c
int drip_link_sign (
    drip_link_t *link,
    drip_link_sign_cb_t callback,
    void *context
) 
```


Signs the DRIP Link using the provided callback and parent private key. Pass the private key in the context.


````cpp
int rc = drip_link_sign(&link, sign_ed25519, (void *)secret_key);
````





**Parameters:**


* `link` Pointer to the DRIP Link to sign. 
* `callback` Callback function used to generate the signature. 
* `context` Opaque context passed to the callback.


**Return value:**


* `DRIP_SUCCESS` if link was signed. 
* `DRIP_ERROR_NULL_POINTER` if link or callback is NULL. 
* `DRIP_ERROR_CALLBACK_FAILED` if callback returned an error. 
* `DRIP_ERROR_INVALID_LENGTH` if the signature is not DRIP\_SIGNATURE\_SIZE.


**See also:** [https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2](https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2)
### function `drip_link_to_json`

_Serialize a DRIP link to a JSON string._
```c
int drip_link_to_json (
    const drip_link_t *link,
    char *buffer,
    size_t buffer_size,
    size_t *json_length
) 
```


On success writes a NULL terminated JSON to buffer. When buffer\_size is too small the output is truncated and DRIP\_ERROR\_BUFFER\_TOO\_SMALL is returned. The truncated buffer is still NULL terminated.



**Parameters:**


* `link` Pointer to the link to serialize. 
* `buffer` Output buffer for the JSON representation. 
* `buffer_size` Size of buffer in bytes. 
* `json_length` Optional. Receives receives the number of characters for the full non truncated output. Ignored if NULL.


**Return value:**


* `DRIP_SUCCESS` on success. 
* `DRIP_ERROR_NULL_POINTER` if link or buffer is NULL. 
* `DRIP_ERROR_BUFFER_TOO_SMALL` if buffer\_size is too small.
### function `drip_link_validate`

_Validate the structural state of a DRIP Link._
```c
int drip_link_validate (
    const drip_link_t *link
) 
```


Performs structural checks only. Does not verify the signature or DET hashes. Use [**drip\_link\_verify()**](#function-drip_link_verify) or[**drip\_link\_verify\_chain()**](#function-drip_link_verify_chain) for that.



**Parameters:**


* `link` Pointer to the DRIP Link to validate.


**Return value:**


* `DRIP_SUCCESS` if link is structurally valid. 
* `DRIP_ERROR_NULL_POINTER` if link is NULL. 
* `DRIP_ERROR_INVALID_SAM_TYPE` if sam\_type is not DRIP\_SAM\_TYPE\_LINK. 
* `DRIP_ERROR_INVALID_TIMESTAMP` if vnb &gt; vna. 
* `DRIP_ERROR_INVALID_CHILD_DET` if child\_det fails validation. 
* `DRIP_ERROR_INVALID_PARENT_DET` if parent\_det fails validation.


**See also:** [https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2](https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2)
### function `drip_link_verify`

_Verify the signature of a DRIP Link._
```c
int drip_link_verify (
    const drip_link_t *link,
    uint32_t unixtime,
    drip_link_verify_cb_t callback,
    void *context
) 
```


Verifies the signature using the provided callback, timestamp and parent HI. Parent HI is the public key, pass it in the context.


````cpp
const drip_hi_t *parent_hi = drip_link_get_child_hi(&parent_link);
uint32_t unixtime = (uint32_t)time(NULL);
int rc = drip_link_verify(&child_link, unixtime, verify_ed25519, (void *)parent_hi);
````





**Parameters:**


* `link` Pointer to the DRIP Link to verify. 
* `unixtime` Unix time in seconds or 0 to ignore. 
* `callback` Callback function used to verify the signature. 
* `context` Opaque context passed to the callback.


**Return value:**


* `DRIP_SUCCESS` if the signature verifies. 
* `DRIP_ERROR_NULL_POINTER` if link or callback is NULL. 
* `DRIP_ERROR_TIMESTAMP_NOT_YET_VALID` if unixtime is before vnb. 
* `DRIP_ERROR_TIMESTAMP_EXPIRED` if unixtime is after vna. 
* `DRIP_ERROR_CALLBACK_FAILED` if callback returned an error.


**See also:** [https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2](https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2)
### function `drip_link_verify_chain`

_Verify a chain of DRIP Links from a trusted root._
```c
int drip_link_verify_chain (
    const drip_link_t *link_array,
    size_t link_count,
    const drip_det_t *root_det,
    const drip_hi_t *root_hi,
    uint32_t unixtime,
    drip_hash_cb_t hash_cb,
    drip_link_verify_cb_t verify_cb
) 
```


**Parameters:**


* `link_array` Array of DRIP Links. 
* `link_count` Number of DRIP Links in link\_array. 
* `root_det` Trusted root DET. 
* `root_hi` Trusted root Host Identity. 
* `unixtime` Unix time in seconds or 0 ignore. 
* `hash_cb` Callback used to verify each child DET hash. 
* `verify_cb` Callback used to verify each DRIP Link signature.


**Return value:**


* `DRIP_SUCCESS` if the chain verifies. 
* `DRIP_ERROR_NULL_POINTER` if link\_array, root\_det, root\_hi, hash\_cb, or verify\_cb is NULL. 
* `DRIP_ERROR_TIMESTAMP_NOT_YET_VALID` if unixtime is before a hop vnb. 
* `DRIP_ERROR_TIMESTAMP_EXPIRED` if unixtime is after a hop vna. 
* `DRIP_ERROR_CALLBACK_FAILED` if a callback returned an error. 
* `DRIP_ERROR_VERIFICATION_FAILED` if a hop DET hash or signature does not match or the chain is broken. 
* `DRIP_ERROR_INVALID_APEX_DELEGATION` if a hop parent is Apex and child is not an RAA. 
* `DRIP_ERROR_INVALID_RAA_DELEGATION` if a hop parent is RAA and child is not an HDA with the same RAA. 
* `DRIP_ERROR_INVALID_HDA_DELEGATION` if a hop parent is HDA and child is not an HDA with the same RAA and HDA.


**See also:** [https://www.rfc-editor.org/rfc/rfc9575.html#section-3.1.2](https://www.rfc-editor.org/rfc/rfc9575.html#section-3.1.2)

**See also:** [https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2](https://www.rfc-editor.org/rfc/rfc9575.html#section-4.2)

## Macros Documentation

### define `DRIP_LINK_SIZE`

```c
#define DRIP_LINK_SIZE 137
```


## File include/drip/manifest.h





## Structures and Types

| Type | Name |
| ---: | :--- |
| typedef int(\* | [**drip\_manifest\_sign\_cb\_t**](#typedef-drip_manifest_sign_cb_t)  <br>_Callback function type for producing manifest signatures._ |
| struct | [**drip\_manifest\_t**](#struct-drip_manifest_t) <br> |
| typedef int(\* | [**drip\_manifest\_verify\_cb\_t**](#typedef-drip_manifest_verify_cb_t)  <br>_Callback function type for verifying manifest signatures._ |

## Functions

| Type | Name |
| ---: | :--- |
|  int | [**drip\_manifest\_add\_evidence**](#function-drip_manifest_add_evidence) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, const [**drip\_hash\_t**](#typedef-drip_hash_t) \*hash) <br> |
|  int | [**drip\_manifest\_decode**](#function-drip_manifest_decode) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, const uint8\_t \*buffer, size\_t buffer\_size) <br>_Decode a manifest from its wire format._ |
|  int | [**drip\_manifest\_encode**](#function-drip_manifest_encode) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, uint8\_t \*buffer, size\_t buffer\_size, size\_t \*encoded\_length) <br> |
|  const [**drip\_hash\_t**](#typedef-drip_hash_t) \* | [**drip\_manifest\_get\_current\_hash**](#function-drip_manifest_get_current_hash) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br> |
|  const [**drip\_det\_t**](#typedef-drip_det_t) \* | [**drip\_manifest\_get\_det**](#function-drip_manifest_get_det) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br> |
|  const [**drip\_hash\_t**](#typedef-drip_hash_t) \* | [**drip\_manifest\_get\_evidence\_at**](#function-drip_manifest_get_evidence_at) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, uint8\_t index) <br> |
|  const [**drip\_hash\_t**](#typedef-drip_hash_t) \* | [**drip\_manifest\_get\_link\_hash**](#function-drip_manifest_get_link_hash) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br> |
|  const [**drip\_hash\_t**](#typedef-drip_hash_t) \* | [**drip\_manifest\_get\_previous\_hash**](#function-drip_manifest_get_previous_hash) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br> |
|  const [**drip\_signature\_t**](#typedef-drip_signature_t) \* | [**drip\_manifest\_get\_signature**](#function-drip_manifest_get_signature) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br> |
|  uint32\_t | [**drip\_manifest\_get\_vna**](#function-drip_manifest_get_vna) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br>_Get the vna timestamp._ |
|  uint32\_t | [**drip\_manifest\_get\_vna\_unixtime**](#function-drip_manifest_get_vna_unixtime) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br>_Get the vna as a unix timestamp._ |
|  uint32\_t | [**drip\_manifest\_get\_vnb**](#function-drip_manifest_get_vnb) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br>_Get the vnb timestamp._ |
|  uint32\_t | [**drip\_manifest\_get\_vnb\_unixtime**](#function-drip_manifest_get_vnb_unixtime) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br>_Get the vnb as a unix timestamp._ |
|  int | [**drip\_manifest\_init**](#function-drip_manifest_init) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br> |
|  int | [**drip\_manifest\_set\_det**](#function-drip_manifest_set_det) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, const [**drip\_det\_t**](#typedef-drip_det_t) \*det) <br> |
|  int | [**drip\_manifest\_set\_link\_hash**](#function-drip_manifest_set_link_hash) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, const [**drip\_hash\_t**](#typedef-drip_hash_t) \*hash) <br> |
|  int | [**drip\_manifest\_set\_previous\_hash**](#function-drip_manifest_set_previous_hash) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, const [**drip\_hash\_t**](#typedef-drip_hash_t) \*hash) <br> |
|  int | [**drip\_manifest\_set\_signature**](#function-drip_manifest_set_signature) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, const [**drip\_signature\_t**](#typedef-drip_signature_t) \*signature) <br> |
|  int | [**drip\_manifest\_set\_vna**](#function-drip_manifest_set_vna) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, uint32\_t vna) <br>_Set the vna timestamp._ |
|  int | [**drip\_manifest\_set\_vna\_unixtime**](#function-drip_manifest_set_vna_unixtime) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, uint32\_t unixtime) <br>_Set the vna from unix timestamp._ |
|  int | [**drip\_manifest\_set\_vnb**](#function-drip_manifest_set_vnb) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, uint32\_t vnb) <br>_Set the vnb timestamp._ |
|  int | [**drip\_manifest\_set\_vnb\_unixtime**](#function-drip_manifest_set_vnb_unixtime) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, uint32\_t unixtime) <br>_Set the vnb from unix timestamp._ |
|  int | [**drip\_manifest\_sign**](#function-drip_manifest_sign) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, [**drip\_manifest\_sign\_cb\_t**](#typedef-drip_manifest_sign_cb_t) callback, void \*context) <br>_Sign a manifest with caller supplied callback._ |
|  int | [**drip\_manifest\_to\_json**](#function-drip_manifest_to_json) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, char \*buffer, size\_t buffer\_size, size\_t \*json\_length) <br>_Serialize a DRIP manifest to a JSON string._ |
|  int | [**drip\_manifest\_update\_current\_hash**](#function-drip_manifest_update_current_hash) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, [**drip\_hash\_cb\_t**](#typedef-drip_hash_cb_t) callback, void \*context) <br>_Update the current hash of a manifest._ |
|  int | [**drip\_manifest\_validate**](#function-drip_manifest_validate) (const [**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest) <br>_Validate the structural state of a manifest._ |
|  int | [**drip\_manifest\_verify**](#function-drip_manifest_verify) ([**drip\_manifest\_t**](#struct-drip_manifest_t) \*manifest, [**drip\_manifest\_verify\_cb\_t**](#typedef-drip_manifest_verify_cb_t) callback, void \*context) <br> |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**DRIP\_EVIDENCE\_SIZE**](#define-drip_evidence_size)  112<br> |
| define  | [**DRIP\_MANIFEST\_EVIDENCE\_MAX**](#define-drip_manifest_evidence_max)  11<br> |
| define  | [**DRIP\_MANIFEST\_HASH\_CUSTOMIZATION**](#define-drip_manifest_hash_customization)  "Remote ID Auth Hash"<br>_RFC 9575 hash customization string for Remote ID authentication hashes._ |
| define  | [**DRIP\_MANIFEST\_MAX\_SIZE**](#define-drip_manifest_max_size)  201 /\* when 11 hashes \*/<br> |
| define  | [**DRIP\_MANIFEST\_MIN\_SIZE**](#define-drip_manifest_min_size)  113 /\* when zero hashes \*/<br> |
| define  | [**DRIP\_SAM\_TYPE\_SIZE**](#define-drip_sam_type_size)  1<br> |
| define  | [**DRIP\_TIMESTAMP\_SIZE**](#define-drip_timestamp_size)  4<br> |

## Structures and Types Documentation

### typedef `drip_manifest_sign_cb_t`

_Callback function type for producing manifest signatures._
```c
typedef int(* drip_manifest_sign_cb_t) (void *context, const uint8_t *input, size_t input_length, uint8_t *buffer, size_t buffer_size, size_t *output_length);
```


Called by [**drip\_manifest\_sign()**](#function-drip_manifest_sign) to perform the actual signing of the payload.



**Parameters:**


* `context` Opaque context passed to the callback. 
* `input` Pointer to the payload to sign. 
* `input_length` Length of the payload in bytes. 
* `buffer` Output buffer for the signature. 
* `buffer_size` Size of the signature buffer in bytes. 
* `output_length` Receives resulting manifest length written.


**Return value:**


* `0` on success. 
* `Non-zero` on signing failure.
### struct `drip_manifest_t`


Variables:

-  [**drip\_hash\_t**](#typedef-drip_hash_t) current_hash  

-  [**drip\_det\_t**](#typedef-drip_det_t) det  

-  [**drip\_hash\_t**](#typedef-drip_hash_t) evidence  

-  uint8\_t evidence_count  

-  [**drip\_hash\_t**](#typedef-drip_hash_t) link_hash  

-  [**drip\_hash\_t**](#typedef-drip_hash_t) previous_hash  

-  uint8\_t sam_type  

-  [**drip\_signature\_t**](#typedef-drip_signature_t) signature  

-  uint32\_t vna  

-  uint32\_t vnb  

### typedef `drip_manifest_verify_cb_t`

_Callback function type for verifying manifest signatures._
```c
typedef int(* drip_manifest_verify_cb_t) (void *context, const uint8_t *input, size_t input_length, const uint8_t *signature, size_t signature_length);
```


Called by [**drip\_manifest\_verify()**](#function-drip_manifest_verify) to perform the actual verification of the signed payload.



**Parameters:**


* `context` Opaque context passed to the callback. 
* `input` Pointer to the signed payload data. 
* `input_length` Length of the signed payload in bytes. 
* `signature` Pointer to the signature to verify against. 
* `signature_length` Length of the signature in bytes.


**Return value:**


* `0` on success. 
* `Non-zero` on verification failure.

## Functions Documentation

### function `drip_manifest_add_evidence`

```c
int drip_manifest_add_evidence (
    drip_manifest_t *manifest,
    const drip_hash_t *hash
) 
```

### function `drip_manifest_decode`

_Decode a manifest from its wire format._
```c
int drip_manifest_decode (
    drip_manifest_t *manifest,
    const uint8_t *buffer,
    size_t buffer_size
) 
```


The `buffer` must contain only the bytes for the manifest and nothing else.



**Parameters:**


* `manifest` Pointer to the manifest that receives the decoded data. 
* `buffer` Input buffer holding the wire format bytes. 
* `buffer_size` Size of `buffer` in bytes.


**Return value:**


* `DRIP_SUCCESS` on success. 
* `DRIP_ERROR_NULL_POINTER` if `manifest` or`buffer` is NULL.
* `DRIP_ERROR_BUFFER_TOO_SMALL` if `buffer_size` is less than DRIP\_MANIFEST\_MIN\_SIZE.
* `DRIP_ERROR_INVALID_LENGTH` if the evidence payload length is not a multiple of DRIP\_HASH\_SIZE. 
* `DRIP_ERROR_ARRAY_OVERFLOW` if the evidence count would exceed DRIP\_MANIFEST\_EVIDENCE\_MAX. 
* `DRIP_ERROR_INVALID_SAM_TYPE` if the decoded SAM type is not DRIP\_SAM\_TYPE\_MANIFEST.
### function `drip_manifest_encode`

```c
int drip_manifest_encode (
    const drip_manifest_t *manifest,
    uint8_t *buffer,
    size_t buffer_size,
    size_t *encoded_length
) 
```

### function `drip_manifest_get_current_hash`

```c
const drip_hash_t * drip_manifest_get_current_hash (
    const drip_manifest_t *manifest
) 
```

### function `drip_manifest_get_det`

```c
const drip_det_t * drip_manifest_get_det (
    const drip_manifest_t *manifest
) 
```

### function `drip_manifest_get_evidence_at`

```c
const drip_hash_t * drip_manifest_get_evidence_at (
    const drip_manifest_t *manifest,
    uint8_t index
) 
```

### function `drip_manifest_get_link_hash`

```c
const drip_hash_t * drip_manifest_get_link_hash (
    const drip_manifest_t *manifest
) 
```

### function `drip_manifest_get_previous_hash`

```c
const drip_hash_t * drip_manifest_get_previous_hash (
    const drip_manifest_t *manifest
) 
```

### function `drip_manifest_get_signature`

```c
const drip_signature_t * drip_manifest_get_signature (
    const drip_manifest_t *manifest
) 
```

### function `drip_manifest_get_vna`

_Get the vna timestamp._
```c
uint32_t drip_manifest_get_vna (
    const drip_manifest_t *manifest
) 
```


Returned as seconds since DRIP\_TIMESTAMP\_EPOCH.



**Parameters:**


* `manifest` Pointer to the manifest.


**Returns:**

The vna timestamp or 0 if manifest is NULL.
### function `drip_manifest_get_vna_unixtime`

_Get the vna as a unix timestamp._
```c
uint32_t drip_manifest_get_vna_unixtime (
    const drip_manifest_t *manifest
) 
```


**Parameters:**


* `manifest` Pointer to the manifest.


**Returns:**

The vna as unix timestamp or 0 if manifest is NULL.
### function `drip_manifest_get_vnb`

_Get the vnb timestamp._
```c
uint32_t drip_manifest_get_vnb (
    const drip_manifest_t *manifest
) 
```


Returned as seconds since DRIP\_TIMESTAMP\_EPOCH.



**Parameters:**


* `manifest` Pointer to the manifest.


**Returns:**

The vnb timestamp or 0 if manifest is NULL.
### function `drip_manifest_get_vnb_unixtime`

_Get the vnb as a unix timestamp._
```c
uint32_t drip_manifest_get_vnb_unixtime (
    const drip_manifest_t *manifest
) 
```


**Parameters:**


* `manifest` Pointer to the manifest.


**Returns:**

The vnb as unix timestamp or 0 if manifest is NULL.
### function `drip_manifest_init`

```c
int drip_manifest_init (
    drip_manifest_t *manifest
) 
```

### function `drip_manifest_set_det`

```c
int drip_manifest_set_det (
    drip_manifest_t *manifest,
    const drip_det_t *det
) 
```

### function `drip_manifest_set_link_hash`

```c
int drip_manifest_set_link_hash (
    drip_manifest_t *manifest,
    const drip_hash_t *hash
) 
```

### function `drip_manifest_set_previous_hash`

```c
int drip_manifest_set_previous_hash (
    drip_manifest_t *manifest,
    const drip_hash_t *hash
) 
```

### function `drip_manifest_set_signature`

```c
int drip_manifest_set_signature (
    drip_manifest_t *manifest,
    const drip_signature_t *signature
) 
```

### function `drip_manifest_set_vna`

_Set the vna timestamp._
```c
int drip_manifest_set_vna (
    drip_manifest_t *manifest,
    uint32_t vna
) 
```


Stored internally as seconds since DRIP\_TIMESTAMP\_EPOCH.



**Parameters:**


* `manifest` Pointer to the manifest to modify. 
* `vna` Offset from DRIP\_TIMESTAMP\_EPOCH in seconds.


**Return value:**


* `DRIP_SUCCESS` if vna was stored. 
* `DRIP_ERROR_NULL_POINTER` if manifest is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if vna &gt; UINT32\_MAX - DRIP\_TIMESTAMP\_EPOCH.
### function `drip_manifest_set_vna_unixtime`

_Set the vna from unix timestamp._
```c
int drip_manifest_set_vna_unixtime (
    drip_manifest_t *manifest,
    uint32_t unixtime
) 
```


**Parameters:**


* `manifest` Pointer to the manifest to modify. 
* `unixtime` Unix timestamp in seconds.


**Return value:**


* `DRIP_SUCCESS` if vna was stored. 
* `DRIP_ERROR_NULL_POINTER` if manifest is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if unixtime &lt; DRIP\_TIMESTAMP\_EPOCH.
### function `drip_manifest_set_vnb`

_Set the vnb timestamp._
```c
int drip_manifest_set_vnb (
    drip_manifest_t *manifest,
    uint32_t vnb
) 
```


Stored internally as seconds since DRIP\_TIMESTAMP\_EPOCH.



**Parameters:**


* `manifest` Pointer to the manifest to modify. 
* `vnb` Offset from DRIP\_TIMESTAMP\_EPOCH in seconds.


**Return value:**


* `DRIP_SUCCESS` if vnb was stored. 
* `DRIP_ERROR_NULL_POINTER` if manifest is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if vnb &gt; UINT32\_MAX - DRIP\_TIMESTAMP\_EPOCH.
### function `drip_manifest_set_vnb_unixtime`

_Set the vnb from unix timestamp._
```c
int drip_manifest_set_vnb_unixtime (
    drip_manifest_t *manifest,
    uint32_t unixtime
) 
```


**Parameters:**


* `manifest` Pointer to the manifest to modify. 
* `unixtime` Unix timestamp in seconds.


**Return value:**


* `DRIP_SUCCESS` if vnb was stored. 
* `DRIP_ERROR_NULL_POINTER` if manifest is NULL. 
* `DRIP_ERROR_OUT_OF_RANGE` if unixtime &lt; DRIP\_TIMESTAMP\_EPOCH.
### function `drip_manifest_sign`

_Sign a manifest with caller supplied callback._
```c
int drip_manifest_sign (
    drip_manifest_t *manifest,
    drip_manifest_sign_cb_t callback,
    void *context
) 
```


**Parameters:**


* `manifest` Pointer to the manifest to be signed. 
* `callback` Callback function used to generate the signature. 
* `context` Opaque context passed to the callback.


**Precondition:**

You must call [**drip\_manifest\_update\_current\_hash()**](#function-drip_manifest_update_current_hash) atleast once before calling this function.



**Return value:**


* `DRIP_SUCCESS` if signing succeeded. 
* `DRIP_ERROR_NULL_POINTER` if `manifest` or`callback` is NULL.
* `DRIP_ERROR_CALLBACK_FAILED` if `callback` returned non-zero.
### function `drip_manifest_to_json`

_Serialize a DRIP manifest to a JSON string._
```c
int drip_manifest_to_json (
    const drip_manifest_t *manifest,
    char *buffer,
    size_t buffer_size,
    size_t *json_length
) 
```


On success writes a NULL terminated JSON to `buffer`. When`buffer_size` is too small the output is truncated and DRIP\_ERROR\_BUFFER\_TOO\_SMALL is returned. The truncated buffer is still NULL terminated.



**Parameters:**


* `link` Pointer to the manifest to serialize. 
* `buffer` Output buffer for the JSON representation. 
* `buffer_size` Size of `buffer` in bytes.
* `json_length` Optional. Receives receives the number of characters for the full non truncated output. Ignored if NULL.


**Return value:**


* `DRIP_SUCCESS` on success. 
* `DRIP_ERROR_NULL_POINTER` if `link` or`buffer` is NULL.
* `DRIP_ERROR_BUFFER_TOO_SMALL` if `buffer_size` is too small.
### function `drip_manifest_update_current_hash`

_Update the current hash of a manifest._
```c
int drip_manifest_update_current_hash (
    drip_manifest_t *manifest,
    drip_hash_cb_t callback,
    void *context
) 
```


Hashes the previous hash a zeroed current hash and the evidence hashes using the caller supplied callback.



**Parameters:**


* `manifest` Pointer to the manifest to modify. 
* `callback` Callback function used to generate the hash. 
* `context` Opaque context passed to the callback.


**Return value:**


* `DRIP_SUCCESS` if the hash was stored. 
* `DRIP_ERROR_NULL_POINTER` if manifest or callback is NULL. 
* `DRIP_ERROR_CALLBACK_FAILED` if callback returned an error. 
* `DRIP_ERROR_INVALID_LENGTH` if resulting hash size does not match DRIP\_HASH\_SIZE.


**See also:** [https://www.rfc-editor.org/rfc/rfc9575.html#section-4.4.3](https://www.rfc-editor.org/rfc/rfc9575.html#section-4.4.3)
### function `drip_manifest_validate`

_Validate the structural state of a manifest._
```c
int drip_manifest_validate (
    const drip_manifest_t *manifest
) 
```


Performs structural checks only. Does not verify the signature.



**Parameters:**


* `manifest` Pointer to the manifest to validate.


**Return value:**


* `DRIP_SUCCESS` if `manifest` is structurally valid.
* `DRIP_ERROR_NULL_POINTER` if `manifest` is NULL.
* `DRIP_ERROR_INVALID_SAM_TYPE` if `sam_type` is not DRIP\_SAM\_TYPE\_MANIFEST.
* `DRIP_ERROR_INVALID_TIMESTAMP` if `vnb` &gt;`vna`.
* `DRIP_ERROR_ARRAY_OVERFLOW` if `evidence_count` exceeds DRIP\_MANIFEST\_EVIDENCE\_MAX.
* `DRIP_ERROR_INVALID_DET` if `det` fails[**drip\_det\_validate()**](#function-drip_det_validate).
### function `drip_manifest_verify`

```c
int drip_manifest_verify (
    drip_manifest_t *manifest,
    drip_manifest_verify_cb_t callback,
    void *context
) 
```


## Macros Documentation

### define `DRIP_EVIDENCE_SIZE`

```c
#define DRIP_EVIDENCE_SIZE 112
```

### define `DRIP_MANIFEST_EVIDENCE_MAX`

```c
#define DRIP_MANIFEST_EVIDENCE_MAX 11
```

### define `DRIP_MANIFEST_HASH_CUSTOMIZATION`

_RFC 9575 hash customization string for Remote ID authentication hashes._
```c
#define DRIP_MANIFEST_HASH_CUSTOMIZATION "Remote ID Auth Hash"
```

### define `DRIP_MANIFEST_MAX_SIZE`

```c
#define DRIP_MANIFEST_MAX_SIZE 201 /* when 11 hashes */
```

### define `DRIP_MANIFEST_MIN_SIZE`

```c
#define DRIP_MANIFEST_MIN_SIZE 113 /* when zero hashes */
```

### define `DRIP_SAM_TYPE_SIZE`

```c
#define DRIP_SAM_TYPE_SIZE 1
```

### define `DRIP_TIMESTAMP_SIZE`

```c
#define DRIP_TIMESTAMP_SIZE 4
```


