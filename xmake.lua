add_rules("mode.debug", "mode.release")

set_languages("c++17")
add_includedirs("include/metal-cpp")
add_frameworks("Foundation", "Metal", "MetalKit")
-- set_runenv("OBJC_DEBUG_MISSING_POOLS", "YES")

add_includedirs("/Users/aska/Applications/OpenUSD/include")
add_includedirs("/Library/Developer/CommandLineTools/Library/Frameworks/Python3.framework/Versions/3.9/Headers")
-- add_defines("PXR_USE_INTERNAL_BOOST_PYTHON")

add_linkdirs("/Users/aska/Applications/OpenUSD/lib")


-- add_requires("cmake::pxr")

target("hdVortex")
    set_kind("shared")
    set_pcheader("src/pch.h")
    add_files("src/*.cpp")
    -- add_packages("cmake::pxr")
    add_links(
        "/Users/aska/Applications/OpenUSD/lib/libusd_ms.dylib",
        "/Users/aska/Applications/OpenUSD/lib/libusd_boost.dylib")
        -- "/Users/aska/Applications/OpenUSD/lib/libusd_usd.dylib",
        -- "/Users/aska/Applications/OpenUSD/lib/libusd_hdSt.dylib",
        -- "/Users/aska/Applications/OpenUSD/lib/libusd_tf.dylib",
        -- "/Users/aska/Applications/OpenUSD/lib/libusd_hf.dylib",
        -- "/Users/aska/Applications/OpenUSD/lib/libusd_hd.dylib")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

