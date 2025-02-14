#include "Base.h"
#include "Archive.h"

EXTERN_C_BEGIN

Void ParseBool(
    CString Value,
    Bool* Result
);

Void ParseInt8(
    CString Value,
    Int8* Result
);

Void ParseInt16(
    CString Value,
    Int16* Result
);

Void ParseInt32(
    CString Value,
    Int32* Result
);

Void ParseInt64(
    CString Value,
    Int64* Result
);

Void ParseUInt8(
    CString Value,
    UInt8* Result
);

Void ParseUInt16(
    CString Value,
    UInt16* Result
);

Void ParseUInt32(
    CString Value,
    UInt32* Result
);

Void ParseUInt64(
    CString Value,
    UInt64* Result
);

Bool ParseAttributeInt8(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Int8* Result
);

Bool ParseAttributeInt16(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Int16* Result
);

Bool ParseAttributeInt32(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Int32* Result
);

Bool ParseAttributeInt64(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Int64* Result
);

Bool ParseAttributeUInt8(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    UInt8* Result
);

Bool ParseAttributeUInt16(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    UInt16* Result
);

Bool ParseAttributeUInt32(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    UInt32* Result
);

Bool ParseAttributeUInt64(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    UInt64* Result
);

Bool ParseAttributeIndex(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Index* Result
);

Bool ParseAttributeFloat32(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Float32* Result
);

Bool ParseAttributeInt32Array(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Int32* Result,
    Int64 Count,
    Char Separator
);

Int32 ParseAttributeInt32ArrayCounted(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Int32* Result,
    Int64 Count,
    Char Separator
);

Bool ParseAttributeUInt32Array(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    UInt32* Result,
    Int64 Count
);

Int32 ParseAttributeInt32Array2D(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    Int32* Result,
    Int64 Count,
    Int64 GroupCount,
    Char Separator,
    Char GroupSeparator
);

Bool ParseAttributeString(
    ArchiveRef Object,
    Int64 NodeIndex,
    CString Name,
    CString Result,
    Int64 Length
);

EXTERN_C_END
