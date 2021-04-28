from setuptools import setup

# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir

import sys

__version__ = "0.0.3"

zlib = (
    'zlib',
    {
        'sources': [
            'external/zlib/adler32.c',
            'external/zlib/compress.c',
            'external/zlib/crc32.c',
            'external/zlib/deflate.c',
            'external/zlib/gzclose.c',
            'external/zlib/gzlib.c',
            'external/zlib/gzread.c',
            'external/zlib/gzwrite.c',
            'external/zlib/infback.c',
            'external/zlib/inffast.c',
            'external/zlib/inflate.c',
            'external/zlib/inftrees.c',
            'external/zlib/trees.c',
            'external/zlib/uncompr.c',
            'external/zlib/zutil.c',
        ],
        'include_dirs': [
            'external/zlib',
        ],
    }
)

onig = (
    'onig',
    {
        'sources': [
            'external/onig/src/ascii.c',
            'external/onig/src/big5.c',
            'external/onig/src/cp1251.c',
            'external/onig/src/euc_jp.c',
            'external/onig/src/euc_jp_prop.c',
            'external/onig/src/euc_kr.c',
            'external/onig/src/euc_tw.c',
            'external/onig/src/gb18030.c',
            'external/onig/src/iso8859_1.c',
            'external/onig/src/iso8859_10.c',
            'external/onig/src/iso8859_11.c',
            'external/onig/src/iso8859_13.c',
            'external/onig/src/iso8859_14.c',
            'external/onig/src/iso8859_15.c',
            'external/onig/src/iso8859_16.c',
            'external/onig/src/iso8859_2.c',
            'external/onig/src/iso8859_3.c',
            'external/onig/src/iso8859_4.c',
            'external/onig/src/iso8859_5.c',
            'external/onig/src/iso8859_6.c',
            'external/onig/src/iso8859_7.c',
            'external/onig/src/iso8859_8.c',
            'external/onig/src/iso8859_9.c',
            'external/onig/src/koi8_r.c',
            'external/onig/src/onig_init.c',
            'external/onig/src/regcomp.c',
            'external/onig/src/regenc.c',
            'external/onig/src/regerror.c',
            'external/onig/src/regexec.c',
            'external/onig/src/regext.c',
            'external/onig/src/reggnu.c',
            'external/onig/src/regparse.c',
            'external/onig/src/regposerr.c',
            'external/onig/src/regposix.c',
            'external/onig/src/regsyntax.c',
            'external/onig/src/regtrav.c',
            'external/onig/src/regversion.c',
            'external/onig/src/sjis.c',
            'external/onig/src/sjis_prop.c',
            'external/onig/src/st.c',
            'external/onig/src/unicode.c',
            'external/onig/src/unicode_fold1_key.c',
            'external/onig/src/unicode_fold2_key.c',
            'external/onig/src/unicode_fold3_key.c',
            'external/onig/src/unicode_unfold_key.c',
            'external/onig/src/utf16_be.c',
            'external/onig/src/utf16_le.c',
            'external/onig/src/utf32_be.c',
            'external/onig/src/utf32_le.c',
            'external/onig/src/utf8.c',
        ],
        'include_dirs': [
            'external/onig',
            'external/onig/src',
        ],
    }
)

krkr_minimal = (
    'krkr_minimal',
    {
        'sources' : [
            'src/krkr_minimal/base/CharacterSet.cpp',
            'src/krkr_minimal/base/StorageIntf.cpp',
            'src/krkr_minimal/base/XP3Archive.cpp',
            'src/krkr_minimal/base/TextStream.cpp',
            'src/krkr_minimal/base/BinaryStream.cpp',
            'src/krkr_minimal/base/UtilStreams.cpp',
            'src/krkr_minimal/msg/android/MsgImpl.cpp',
            'src/krkr_minimal/msg/android/MsgLoad.cpp',
            'src/krkr_minimal/msg/MsgIntf.cpp',
            'src/krkr_minimal/tjs2/tjs.cpp',
            'src/krkr_minimal/tjs2/tjs.tab.cpp',
            'src/krkr_minimal/tjs2/tjsArray.cpp',
            'src/krkr_minimal/tjs2/tjsBinarySerializer.cpp',
            'src/krkr_minimal/tjs2/tjsByteCodeLoader.cpp',
            'src/krkr_minimal/tjs2/tjsCompileControl.cpp',
            'src/krkr_minimal/tjs2/tjsConfig.cpp',
            'src/krkr_minimal/tjs2/tjsConstArrayData.cpp',
            'src/krkr_minimal/tjs2/tjsDate.cpp',
            'src/krkr_minimal/tjs2/tjsDateParser.cpp',
            'src/krkr_minimal/tjs2/tjsDebug.cpp',
            'src/krkr_minimal/tjs2/tjsDictionary.cpp',
            'src/krkr_minimal/tjs2/tjsDisassemble.cpp',
            'src/krkr_minimal/tjs2/tjsError.cpp',
            'src/krkr_minimal/tjs2/tjsException.cpp',
            'src/krkr_minimal/tjs2/tjsGlobalStringMap.cpp',
            'src/krkr_minimal/tjs2/tjsInterCodeExec.cpp',
            'src/krkr_minimal/tjs2/tjsInterCodeGen.cpp',
            'src/krkr_minimal/tjs2/tjsInterface.cpp',
            'src/krkr_minimal/tjs2/tjsLex.cpp',
            'src/krkr_minimal/tjs2/tjsMT19937ar-cok.cpp',
            'src/krkr_minimal/tjs2/tjsMath.cpp',
            'src/krkr_minimal/tjs2/tjsMessage.cpp',
            'src/krkr_minimal/tjs2/tjsNamespace.cpp',
            'src/krkr_minimal/tjs2/tjsNative.cpp',
            'src/krkr_minimal/tjs2/tjsObject.cpp',
            'src/krkr_minimal/tjs2/tjsObjectExtendable.cpp',
            'src/krkr_minimal/tjs2/tjsOctPack.cpp',
            'src/krkr_minimal/tjs2/tjsRandomGenerator.cpp',
            'src/krkr_minimal/tjs2/tjsRegExp.cpp',
            'src/krkr_minimal/tjs2/tjsScriptBlock.cpp',
            'src/krkr_minimal/tjs2/tjsScriptCache.cpp',
            'src/krkr_minimal/tjs2/tjsSnprintf.cpp',
            'src/krkr_minimal/tjs2/tjsString.cpp',
            'src/krkr_minimal/tjs2/tjsUtils.cpp',
            'src/krkr_minimal/tjs2/tjsVariant.cpp',
            'src/krkr_minimal/tjs2/tjsVariantString.cpp',
            'src/krkr_minimal/tjs2/tjsdate.tab.cpp',
            'src/krkr_minimal/tjs2/tjspp.tab.cpp',
            'src/krkr_minimal/utils/DebugIntf.cpp',
            'src/krkr_minimal/utils/cp932_uni.cpp',
            'src/krkr_minimal/utils/uni_cp932.cpp',
        ],
        'include_dirs': [
            'src/krkr_minimal/base',
            'src/krkr_minimal/msg',
            'src/krkr_minimal/msg/android',
            'src/krkr_minimal/tjs2',
            'src/krkr_minimal/utils',
        ],
        'cflags': [
        ],
        'macros': [
        ]
    }
)

krkr_minimal[1]['include_dirs'] += zlib[1]['include_dirs']
krkr_minimal[1]['include_dirs'] += onig[1]['include_dirs']

if sys.platform.startswith('win'):
    krkr_minimal[1]['sources'] += [
        'src/krkr_minimal/base/win32/StorageImpl.cpp',
    ]
    krkr_minimal[1]['include_dirs'] += [
        'src/krkr_minimal/base/win32',
    ]
    krkr_minimal[1]['macros'] += [
        ('UNICODE', None),
        ('_UNICODE', None),
    ]
else:
    krkr_minimal[1]['sources'] += [
        'src/krkr_minimal/base/android/StorageImpl.cpp',
    ]
    krkr_minimal[1]['include_dirs'] += [
        'src/krkr_minimal/base/android',
    ]
    krkr_minimal[1]['cflags'] += [
        '-std=c++11',
    ]


ext_modules = [
    Pybind11Extension("pytjs",
        sources = ['src/main.cpp'],
        include_dirs = krkr_minimal[1]['include_dirs'],
        define_macros = [
            ('VERSION_INFO', __version__),
        ],
    ),
]

class build_ext_with_custom_flags(build_ext):
    def build_extensions(self):
        compiler = self.compiler.compiler_type

        if ('gcc' in compiler) or ('mingw' in compiler):
            for extension in self.extensions:
                # We need to keep null pointer checks of "this" because some code will cast without checking null.
                extension.extra_compile_args.append('-fno-delete-null-pointer-checks')

        super().build_extensions()

setup(
    name="pytjs",
    version=__version__,
    author="Julian Uy",
    author_email="uyjulian" + "@" + "g" + "mail" + "." + "com",
    url="https://github.com/uyjulian/pytjs",
    description="TJS2 interface to Python",
    long_description="",
    ext_modules=ext_modules,
    libraries=[zlib, onig, krkr_minimal],
    cmdclass={"build_ext": build_ext_with_custom_flags},
    zip_safe=False,
)
