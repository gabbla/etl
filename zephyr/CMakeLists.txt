cmake_minimum_required(VERSION 3.20)

project(etl CXX)

# Helper function to define ETL configuration macros.
# This works because the config names in the Kconfig
# are the same as found in ETL
# Example:
#   etl_compile_definitions_ifdef(ETL_NO_STL)
# Equals to:
#   zephyr_compile_definitions_ifdef(CONFIG_ETL_NO_STL ETL_NO_STL)
function(etl_compile_definitions_ifdef cfg)
    zephyr_compile_definitions_ifdef(CONFIG_${cfg} ${cfg})
endfunction()

if (CONFIG_ETL)
    set(etl_root ${ZEPHYR_CURRENT_MODULE_DIR})
    zephyr_interface_library_named(etl)
    zephyr_include_directories(etl ${etl_root}/include)

    etl_compile_definitions_ifdef(ETL_THROW_EXCEPTIONS)
    etl_compile_definitions_ifdef(ETL_LOG_ERRORS)
    etl_compile_definitions_ifdef(ETL_CHECK_PUSH_POP)
    etl_compile_definitions_ifdef(ETL_VERBOSE_ERRORS)
    etl_compile_definitions_ifdef(ETL_ISTRING_REPAIR_ENABLE)
    etl_compile_definitions_ifdef(ETL_IVECTOR_REPAIR_ENABLE)
    etl_compile_definitions_ifdef(ETL_IDEQUE_REPAIR_ENABLE)
    etl_compile_definitions_ifdef(ETL_NO_STL)
    etl_compile_definitions_ifdef(ETL_FORCE_EXPLICIT_STRING_CONVERSION_FROM_CHAR)
    etl_compile_definitions_ifdef(ETL_ENABLE_ERROR_ON_STRING_TRUNCATION)
    etl_compile_definitions_ifdef(ETL_ARRAY_VIEW_IS_MUTABLE)

    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_MESSAGES)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_CONTAINERS)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_BITSET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_DEQUE)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_FLAT_MAP)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_FLAT_MULTIMAP)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_FLAT_SET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_FLAT_MULTISET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_FORWARD_LIST)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_LIST)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_MAP)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_MULTIMAP)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_SET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_MULTISET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_QUEUE)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_STACK)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_REFERENCE_FLAT_MAP)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_REFERENCE_FLAT_MULTIMAP)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_REFERENCE_FLAT_SET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_REFERENCE_FLAT_MULTISET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_UNORDERED_MAP)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_UNORDERED_MULTIMAP)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_UNORDERED_SET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_UNORDERED_MULTISET)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_STRINGS)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_POOL)
    etl_compile_definitions_ifdef(ETL_POLYMORPHIC_VECTOR)

    etl_compile_definitions_ifdef(ETL_DEBUG)

endif()