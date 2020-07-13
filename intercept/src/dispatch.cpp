/*
// Copyright (c) 2018-2020 Intel Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/

#include <string>

#include "intercept.h"

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetPlatformIDs)(
    cl_uint num_entries,
    cl_platform_id* platforms,
    cl_uint* num_platforms )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetPlatformIDs )
    {
        LOG_CLINFO();

        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetPlatformIDs(
            num_entries,
            platforms,
            num_platforms );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetPlatformInfo)(
    cl_platform_id platform,
    cl_platform_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetPlatformInfo )
    {
        std::string platformInfo;
        if( pIntercept->callLogging() )
        {
            pIntercept->getPlatformInfoString(
                platform,
                platformInfo );
        }
        CALL_LOGGING_ENTER( "platform = [ %s ], param_name = %s (%08X)",
            platformInfo.c_str(),
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = CL_SUCCESS;

        if( pIntercept->overrideGetPlatformInfo(
                platform,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret,
                retVal ) == false )
        {
            retVal = pIntercept->dispatch().clGetPlatformInfo(
                platform,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret );
        }

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetDeviceIDs)(
    cl_platform_id platform,
    cl_device_type device_type,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetDeviceIDs )
    {
        std::string platformInfo;
        if( pIntercept->callLogging() )
        {
            pIntercept->getPlatformInfoString(
                platform,
                platformInfo );
        }
        CALL_LOGGING_ENTER( "platform = [ %s ], device_type = %s (%llX)",
            platformInfo.c_str(),
            pIntercept->enumName().name_device_type( device_type ).c_str(),
            device_type );
        CPU_PERFORMANCE_TIMING_START();

        cl_int retVal = CL_SUCCESS;

        device_type = pIntercept->filterDeviceType( device_type );

        retVal = pIntercept->dispatch().clGetDeviceIDs(
            platform,
            device_type,
            num_entries,
            devices,
            num_devices );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetDeviceInfo)(
    cl_device_id device,
    cl_device_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetDeviceInfo )
    {
        std::string deviceInfo;
        if( pIntercept->callLogging() )
        {
            pIntercept->getDeviceInfoString(
                1,
                &device,
                deviceInfo );
        }
        CALL_LOGGING_ENTER( "device = [ %s ], param_name = %s (%08X)",
            deviceInfo.c_str(),
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = CL_SUCCESS;

        if( pIntercept->overrideGetDeviceInfo(
                device,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret,
                retVal ) == false )
        {
            retVal = pIntercept->dispatch().clGetDeviceInfo(
                device,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret );
        }

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clCreateSubDevices)(
    cl_device_id in_device,
    const cl_device_partition_property* properties,
    cl_uint num_devices,
    cl_device_id* out_devices,
    cl_uint* num_devices_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateSubDevices )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clCreateSubDevices(
            in_device,
            properties,
            num_devices,
            out_devices,
            num_devices_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        if( pIntercept->config().LeakChecking &&
            out_devices &&
            num_devices_ret )
        {
            for( cl_uint d = 0; d < num_devices_ret[0]; d++ )
            {
                ADD_OBJECT_ALLOCATION( out_devices[d] );
            }
        }
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clRetainDevice)(
    cl_device_id device )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clRetainDevice )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetDeviceInfo(
                device,
                CL_DEVICE_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] device = %p",
            ref_count,
            device );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clRetainDevice(
            device );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RETAIN( device );
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetDeviceInfo(
                device,
                CL_DEVICE_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clReleaseDevice)(
    cl_device_id device )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clReleaseDevice )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetDeviceInfo(
                device,
                CL_DEVICE_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] device = %p",
            ref_count,
            device );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clReleaseDevice(
            device );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RELEASE( device );
        if( pIntercept->callLogging() && ref_count != 0 )
        {
            // This isn't strictly correct, but it's pretty close, and it
            // avoids crashes in some cases for bad implementations.
            --ref_count;
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

#ifdef __ANDROID__
//Workaround for Android, shared library destructor isn't called
static int contextCount = 0;
static std::mutex mContextCount;
#endif

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_context CL_API_CALL CLIRN(clCreateContext)(
    const cl_context_properties* properties,
    cl_uint num_devices,
    const cl_device_id* devices,
    void (CL_CALLBACK *pfn_notify)(const char *, const void *, size_t, void *),
    void* user_data,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateContext )
    {
        cl_context_properties*  newProperties = NULL;
        cl_context  retVal = NULL;

        std::string contextProperties;
        std::string deviceInfo;
        if( pIntercept->callLogging() )
        {
            pIntercept->getContextPropertiesString(
                properties,
                contextProperties );
            pIntercept->getDeviceInfoString(
                num_devices,
                devices,
                deviceInfo );
        }
        CALL_LOGGING_ENTER( "properties = [ %s ], num_devices = %d, devices = [ %s ]",
            contextProperties.c_str(),
            num_devices,
            deviceInfo.c_str() );
        CREATE_CONTEXT_OVERRIDE_INIT( properties, pfn_notify, user_data, newProperties );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        if( ( retVal == NULL ) && newProperties )
        {
            retVal = pIntercept->dispatch().clCreateContext(
                newProperties,
                num_devices,
                devices,
                pfn_notify,
                user_data,
                errcode_ret );
        }
        if( retVal == NULL )
        {
            retVal = pIntercept->dispatch().clCreateContext(
                properties,
                num_devices,
                devices,
                pfn_notify,
                user_data,
                errcode_ret );
        }

        ITT_ADD_PARAM_AS_METADATA( retVal );

        INIT_PRECOMPILED_KERNEL_OVERRIDES( retVal );
        INIT_BUILTIN_KERNEL_OVERRIDES( retVal );

        CPU_PERFORMANCE_TIMING_END();
        CREATE_CONTEXT_OVERRIDE_CLEANUP( retVal, newProperties );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

#ifdef __ANDROID__
        mContextCount.lock();
        contextCount ++;
        mContextCount.unlock();
#endif
        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_context CL_API_CALL CLIRN(clCreateContextFromType)(
    const cl_context_properties* properties,
    cl_device_type device_type,
    void (CL_CALLBACK *pfn_notify)(const char *, const void *, size_t, void *),
    void* user_data,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateContextFromType )
    {
        cl_context_properties*  newProperties = NULL;
        cl_context  retVal = NULL;

        std::string contextProperties;
        if( pIntercept->callLogging() )
        {
            pIntercept->getContextPropertiesString(
                properties,
                contextProperties );
        }
        CALL_LOGGING_ENTER( "properties = [ %s ], device_type = %s (%llX)",
            contextProperties.c_str(),
            pIntercept->enumName().name_device_type( device_type ).c_str(),
            device_type );
        CREATE_CONTEXT_OVERRIDE_INIT( properties, pfn_notify, user_data, newProperties );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        device_type = pIntercept->filterDeviceType( device_type );

        if( ( retVal == NULL ) && newProperties )
        {
            retVal = pIntercept->dispatch().clCreateContextFromType(
                newProperties,
                device_type,
                pfn_notify,
                user_data,
                errcode_ret );
        }
        if( retVal == NULL )
        {
            retVal = pIntercept->dispatch().clCreateContextFromType(
                properties,
                device_type,
                pfn_notify,
                user_data,
                errcode_ret );
        }

        ITT_ADD_PARAM_AS_METADATA( retVal );

        INIT_PRECOMPILED_KERNEL_OVERRIDES( retVal );
        INIT_BUILTIN_KERNEL_OVERRIDES( retVal );

        CPU_PERFORMANCE_TIMING_END();
        CREATE_CONTEXT_OVERRIDE_CLEANUP( retVal, newProperties );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

#ifdef __ANDROID__
        mContextCount.lock();
        contextCount ++;
        mContextCount.unlock();
#endif
        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clRetainContext)(
    cl_context context )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clRetainContext )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetContextInfo(
                context,
                CL_CONTEXT_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] context = %p",
            ref_count,
            context );
        CPU_PERFORMANCE_TIMING_START();

        cl_int retVal = pIntercept->dispatch().clRetainContext(
            context );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RETAIN( context );
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetContextInfo(
                context,
                CL_CONTEXT_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clReleaseContext)(
    cl_context context )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clReleaseContext )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetContextInfo(
                context,
                CL_CONTEXT_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] context = %p",
            ref_count,
            context );
        CPU_PERFORMANCE_TIMING_START();

        cl_int retVal = pIntercept->dispatch().clReleaseContext(
            context );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RELEASE( context );
        if( pIntercept->callLogging() && ref_count != 0 )
        {
            // This isn't strictly correct, but it's pretty close, and it
            // avoids crashes in some cases for bad implementations.
            --ref_count;
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

#if 0
        pIntercept->report();
#endif

#ifdef __ANDROID__
        mContextCount.lock();
        contextCount --;
        mContextCount.unlock();

        if( contextCount == 0 )
        {
            pIntercept->report();
        }
#endif
        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetContextInfo)(
    cl_context context,
    cl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetContextInfo )
    {
        CALL_LOGGING_ENTER( "param_name = %s (%08X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int retVal = pIntercept->dispatch().clGetContextInfo(
            context,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_command_queue CL_API_CALL CLIRN(clCreateCommandQueue)(
    cl_context context,
    cl_device_id device,
    cl_command_queue_properties properties,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateCommandQueue )
    {
        cl_queue_properties*    newProperties = NULL;
        cl_command_queue    retVal = NULL;

        std::string deviceInfo;
        if( pIntercept->callLogging() )
        {
            pIntercept->getDeviceInfoString(
                1,
                &device,
                deviceInfo );
        }
        CALL_LOGGING_ENTER( "context = %p, device = [ %s ], properties = %s (%llX)",
            context,
            deviceInfo.c_str(),
            pIntercept->enumName().name_command_queue_properties( properties ).c_str(),
            properties );
        CREATE_COMMAND_QUEUE_PROPERTIES_INIT( device, properties, newProperties );

        pIntercept->modifyCommandQueueProperties( properties );

        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

#if defined(USE_MDAPI)
        if( pIntercept->config().DevicePerfCounterEventBasedSampling )
        {
            if( ( retVal == NULL ) && newProperties )
            {
                retVal = pIntercept->createMDAPICommandQueue(
                    context,
                    device,
                    newProperties,
                    errcode_ret );
            }
            if( retVal == NULL )
            {
                retVal = pIntercept->createMDAPICommandQueue(
                    context,
                    device,
                    properties,
                    errcode_ret );
            }
        }
#endif

        if( ( retVal == NULL ) && newProperties )
        {
            retVal = pIntercept->createCommandQueueWithProperties(
                context,
                device,
                newProperties,
                errcode_ret );
        }
        if( retVal == NULL )
        {
            retVal = pIntercept->dispatch().clCreateCommandQueue(
                context,
                device,
                properties,
                errcode_ret );
        }

        CPU_PERFORMANCE_TIMING_END();
        CREATE_COMMAND_QUEUE_PROPERTIES_CLEANUP( newProperties );
        CHECK_ERROR( errcode_ret[0] );
        ITT_REGISTER_COMMAND_QUEUE( retVal, false );
        CHROME_REGISTER_COMMAND_QUEUE( retVal );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clRetainCommandQueue)(
    cl_command_queue command_queue )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clRetainCommandQueue )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetCommandQueueInfo(
                command_queue,
                CL_QUEUE_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] command_queue = %p",
            ref_count,
            command_queue );
        CPU_PERFORMANCE_TIMING_START();

        cl_int retVal = pIntercept->dispatch().clRetainCommandQueue(
            command_queue );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RETAIN( command_queue );
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetCommandQueueInfo(
                command_queue,
                CL_QUEUE_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clReleaseCommandQueue)(
    cl_command_queue command_queue )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clReleaseCommandQueue )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetCommandQueueInfo(
                command_queue,
                CL_QUEUE_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] command_queue = %p",
            ref_count,
            command_queue );
        CPU_PERFORMANCE_TIMING_START();

        cl_int retVal = pIntercept->dispatch().clReleaseCommandQueue(
            command_queue );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ITT_RELEASE_COMMAND_QUEUE( command_queue );
        ADD_OBJECT_RELEASE( command_queue );
        if( pIntercept->callLogging() && ref_count != 0 )
        {
            // This isn't strictly correct, but it's pretty close, and it
            // avoids crashes in some cases for bad implementations.
            --ref_count;
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetCommandQueueInfo)(
    cl_command_queue command_queue,
    cl_command_queue_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetCommandQueueInfo )
    {
        CALL_LOGGING_ENTER( "param_name = %s (%08X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int retVal = pIntercept->dispatch().clGetCommandQueueInfo(
            command_queue,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetCommandQueueProperty)(
    cl_command_queue command_queue,
    cl_command_queue_properties properties,
    cl_bool enable,
    cl_command_queue_properties* old_properties )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetCommandQueueProperty )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int retVal = pIntercept->dispatch().clSetCommandQueueProperty(
            command_queue,
            properties,
            enable,
            old_properties );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateBuffer)(
    cl_context context,
    cl_mem_flags flags,
    size_t size,
    void* host_ptr,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateBuffer )
    {
        CALL_LOGGING_ENTER( "context = %p, flags = %s (%llX), size = %d, host_ptr = %p",
            context,
            pIntercept->enumName().name_mem_flags( flags ).c_str(),
            flags,
            size,
            host_ptr );
        INITIALIZE_BUFFER_CONTENTS_INIT( flags, size, host_ptr );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_mem  retVal = pIntercept->dispatch().clCreateBuffer(
            context,
            flags,
            size,
            host_ptr,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        ADD_BUFFER( retVal );
        INITIALIZE_BUFFER_CONTENTS_CLEANUP( flags, host_ptr );
        DUMP_BUFFER_AFTER_CREATE( retVal, flags, host_ptr, size );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 3.0
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateBufferWithProperties)(
    cl_context context,
    const cl_mem_properties * properties,
    cl_mem_flags flags,
    size_t size,
    void* host_ptr,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateBufferWithProperties )
    {
        CALL_LOGGING_ENTER( "context = %p, properties = %p, flags = %s (%llX), size = %d, host_ptr = %p",
            context,
            properties,
            pIntercept->enumName().name_mem_flags( flags ).c_str(),
            flags,
            size,
            host_ptr );
        INITIALIZE_BUFFER_CONTENTS_INIT( flags, size, host_ptr );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_mem  retVal = pIntercept->dispatch().clCreateBufferWithProperties(
            context,
            properties,
            flags,
            size,
            host_ptr,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        ADD_BUFFER( retVal );
        INITIALIZE_BUFFER_CONTENTS_CLEANUP( flags, host_ptr );
        DUMP_BUFFER_AFTER_CREATE( retVal, flags, host_ptr, size );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.1
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateSubBuffer)(
    cl_mem buffer,
    cl_mem_flags flags,
    cl_buffer_create_type buffer_create_type,
    const void *buffer_create_info,
    cl_int *errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateSubBuffer )
    {
        std::string argsString;
        if( pIntercept->callLogging() )
        {
            pIntercept->getCreateSubBufferArgsString(
                buffer_create_type,
                buffer_create_info,
                argsString );
        }
        CALL_LOGGING_ENTER( "buffer = %p, flags = %s (%llX), %s",
            buffer,
            pIntercept->enumName().name_mem_flags( flags ).c_str(),
            flags,
            argsString.c_str() );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_mem  retVal = pIntercept->dispatch().clCreateSubBuffer(
            buffer,
            flags,
            buffer_create_type,
            buffer_create_info,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        ADD_BUFFER( retVal );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateImage)(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    const cl_image_desc* image_desc,
    void* host_ptr,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateImage )
    {
        if( image_desc && image_format )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX), "
                "format->channel_order = %s, "
                "format->channel_data_type = %s, "
                "desc->type = %s, "
                "desc->width = %d, "
                "desc->height = %d, "
                "desc->depth = %d, "
                "desc->array_size = %d, "
                "desc->row_pitch = %d, "
                "desc->slice_pitch = %d, "
                "desc->num_mip_levels = %d, "
                "desc->num_samples = %d, "
                "desc->mem_object = %p, "
                "host_ptr = %p ",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags,
                pIntercept->enumName().name( image_format->image_channel_order ).c_str(),
                pIntercept->enumName().name( image_format->image_channel_data_type ).c_str(),
                pIntercept->enumName().name( image_desc->image_type ).c_str(),
                image_desc->image_width,
                image_desc->image_height,
                image_desc->image_depth,
                image_desc->image_array_size,
                image_desc->image_row_pitch,
                image_desc->image_slice_pitch,
                image_desc->num_mip_levels,
                image_desc->num_samples,
                image_desc->mem_object,
                host_ptr );
        }
        else
        {
            CALL_LOGGING_ENTER();
        }

        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_mem  retVal = pIntercept->dispatch().clCreateImage(
            context,
            flags,
            image_format,
            image_desc,
            host_ptr,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        ADD_IMAGE( retVal );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 3.0
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateImageWithProperties)(
    cl_context context,
    const cl_mem_properties* properties,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    const cl_image_desc* image_desc,
    void* host_ptr,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateImageWithProperties )
    {
        if( image_desc && image_format )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "properties = %p, "
                "flags = %s (%llX), "
                "format->channel_order = %s, "
                "format->channel_data_type = %s, "
                "desc->type = %s, "
                "desc->width = %d, "
                "desc->height = %d, "
                "desc->depth = %d, "
                "desc->array_size = %d, "
                "desc->row_pitch = %d, "
                "desc->slice_pitch = %d, "
                "desc->num_mip_levels = %d, "
                "desc->num_samples = %d, "
                "desc->mem_object = %p, "
                "host_ptr = %p ",
                context,
                properties,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags,
                pIntercept->enumName().name( image_format->image_channel_order ).c_str(),
                pIntercept->enumName().name( image_format->image_channel_data_type ).c_str(),
                pIntercept->enumName().name( image_desc->image_type ).c_str(),
                image_desc->image_width,
                image_desc->image_height,
                image_desc->image_depth,
                image_desc->image_array_size,
                image_desc->image_row_pitch,
                image_desc->image_slice_pitch,
                image_desc->num_mip_levels,
                image_desc->num_samples,
                image_desc->mem_object,
                host_ptr );
        }
        else
        {
            CALL_LOGGING_ENTER();
        }

        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_mem  retVal = pIntercept->dispatch().clCreateImageWithProperties(
            context,
            properties,
            flags,
            image_format,
            image_desc,
            host_ptr,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        ADD_IMAGE( retVal );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateImage2D)(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    size_t image_width,
    size_t image_height,
    size_t image_row_pitch,
    void* host_ptr,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateImage2D )
    {
        if( image_format )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX), "
                "format->channel_order = %s, "
                "format->channel_data_type = %s, "
                "image_width = %d, "
                "image_height = %d, "
                "image_row_pitch = %d, "
                "host_ptr = %p ",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags,
                pIntercept->enumName().name( image_format->image_channel_order ).c_str(),
                pIntercept->enumName().name( image_format->image_channel_data_type ).c_str(),
                image_width,
                image_height,
                image_row_pitch,
                host_ptr );
        }
        else
        {
            CALL_LOGGING_ENTER();
        }

        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_mem  retVal = pIntercept->dispatch().clCreateImage2D(
            context,
            flags,
            image_format,
            image_width,
            image_height,
            image_row_pitch,
            host_ptr,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        ADD_IMAGE( retVal );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateImage3D)(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    size_t image_width,
    size_t image_height,
    size_t image_depth,
    size_t image_row_pitch,
    size_t image_slice_pitch,
    void* host_ptr,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateImage3D )
    {
        if( image_format )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX), "
                "format->channel_order = %s, "
                "format->channel_data_type = %s, "
                "image_width = %d, "
                "image_height = %d, "
                "image_row_pitch = %d, "
                "image_slice_pitch = %d, "
                "host_ptr = %p ",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags,
                pIntercept->enumName().name( image_format->image_channel_order ).c_str(),
                pIntercept->enumName().name( image_format->image_channel_data_type ).c_str(),
                image_width,
                image_height,
                image_depth,
                image_row_pitch,
                image_slice_pitch,
                host_ptr );
        }
        else
        {
            CALL_LOGGING_ENTER();
        }

        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_mem  retVal = pIntercept->dispatch().clCreateImage3D(
            context,
            flags,
            image_format,
            image_width,
            image_height,
            image_depth,
            image_row_pitch,
            image_slice_pitch,
            host_ptr,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        ADD_IMAGE( retVal );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clRetainMemObject)(
    cl_mem memobj )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clRetainMemObject )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetMemObjectInfo(
                memobj,
                CL_MEM_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] mem = %p",
            ref_count,
            memobj );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clRetainMemObject(
            memobj );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RETAIN( memobj );
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetMemObjectInfo(
                memobj,
                CL_MEM_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clReleaseMemObject)(
    cl_mem memobj )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clReleaseMemObject )
    {
        REMOVE_MEMOBJ( memobj );

        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetMemObjectInfo(
                memobj,
                CL_MEM_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] mem = %p",
            ref_count,
            memobj );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clReleaseMemObject(
            memobj );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RELEASE( memobj );
        if( pIntercept->callLogging() && ref_count != 0 )
        {
            // This isn't strictly correct, but it's pretty close, and it
            // avoids crashes in some cases for bad implementations.
            --ref_count;
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetSupportedImageFormats)(
    cl_context context,
    cl_mem_flags flags,
    cl_mem_object_type image_type,
    cl_uint num_entries,
    cl_image_format* image_formats,
    cl_uint* num_image_formats )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetSupportedImageFormats )
    {
        CALL_LOGGING_ENTER( "flags = %s (%llX), image_type = %s (%X)",
            pIntercept->enumName().name_mem_flags( flags ).c_str(),
            flags,
            pIntercept->enumName().name( image_type ).c_str(),
            image_type );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetSupportedImageFormats(
            context,
            flags,
            image_type,
            num_entries,
            image_formats,
            num_image_formats );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetMemObjectInfo)(
    cl_mem memobj,
    cl_mem_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetMemObjectInfo )
    {
        CALL_LOGGING_ENTER( "mem = %p, param_name = %s (%08X)",
            memobj,
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetMemObjectInfo(
            memobj,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetImageInfo)(
    cl_mem image,
    cl_image_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetImageInfo )
    {
        CALL_LOGGING_ENTER( "mem = %p, param_name = %s (%08X)",
            image,
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetImageInfo(
            image,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetMemObjectDestructorCallback)(
    cl_mem memobj,
    void (CL_CALLBACK *pfn_notify)( cl_mem, void* ),
    void *user_data )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetMemObjectDestructorCallback )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clSetMemObjectDestructorCallback(
            memobj,
            pfn_notify,
            user_data );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_sampler CL_API_CALL CLIRN(clCreateSampler)(
    cl_context context,
    cl_bool normalized_coords,
    cl_addressing_mode addressing_mode,
    cl_filter_mode filter_mode,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateSampler )
    {
        std::string samplerProperties;
        if( pIntercept->callLogging() )
        {
            cl_sampler_properties sampler_properties[] = {
                CL_SAMPLER_NORMALIZED_COORDS, normalized_coords,
                CL_SAMPLER_ADDRESSING_MODE,   addressing_mode,
                CL_SAMPLER_FILTER_MODE,       filter_mode,
                0
            };
            pIntercept->getSamplerPropertiesString(
                sampler_properties,
                samplerProperties );
        }

        CALL_LOGGING_ENTER( "context = %p, properties = [ %s ]",
            context,
            samplerProperties.c_str() );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_sampler  retVal = pIntercept->dispatch().clCreateSampler(
            context,
            normalized_coords,
            addressing_mode,
            filter_mode,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );
        ADD_SAMPLER(retVal, samplerProperties);

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clRetainSampler)(
    cl_sampler sampler )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clRetainSampler )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetSamplerInfo(
                sampler,
                CL_SAMPLER_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] sampler = %p",
            ref_count,
            sampler );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clRetainSampler(
            sampler );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RETAIN( sampler );
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetSamplerInfo(
                sampler,
                CL_SAMPLER_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clReleaseSampler)(
    cl_sampler sampler )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clReleaseSampler )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            pIntercept->dispatch().clGetSamplerInfo(
                sampler,
                CL_SAMPLER_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] sampler = %p",
            ref_count,
            sampler );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clReleaseSampler(
            sampler );

        if ( --ref_count == 0 )
        {
            pIntercept->removeSampler( sampler );
        }

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RELEASE( sampler );
        if( pIntercept->callLogging() && ref_count != 0 )
        {
            // This isn't strictly correct, but it's pretty close, and it
            // avoids crashes in some cases for bad implementations.
            --ref_count;
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetSamplerInfo)(
    cl_sampler sampler,
    cl_sampler_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetSamplerInfo )
    {
        CALL_LOGGING_ENTER( "param_name = %s (%08X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetSamplerInfo(
            sampler,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_program CL_API_CALL CLIRN(clCreateProgramWithSource)(
    cl_context context,
    cl_uint count,
    const char** strings,
    const size_t* lengths,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateProgramWithSource )
    {
        char*       singleString = NULL;
        uint64_t    hash = 0;

        CREATE_COMBINED_PROGRAM_STRING( count, strings, lengths, singleString, hash );
        INJECT_PROGRAM_SOURCE( count, strings, lengths, singleString, hash );
        PREPEND_PROGRAM_SOURCE( count, strings, lengths, singleString, hash );

        CALL_LOGGING_ENTER( "context = %p, count = %d",
            context,
            count );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_program  retVal = NULL;

        if( ( retVal == NULL ) &&
            pIntercept->config().InjectProgramBinaries )
        {
            retVal = pIntercept->createProgramWithInjectionBinaries(
                hash,
                context,
                errcode_ret );
        }

        if( ( retVal == NULL ) &&
            pIntercept->config().InjectProgramSPIRV )
        {
            retVal = pIntercept->createProgramWithInjectionSPIRV(
                hash,
                context,
                errcode_ret );
        }

        if( retVal == NULL )
        {
            retVal = pIntercept->dispatch().clCreateProgramWithSource(
                context,
                count,
                strings,
                lengths,
                errcode_ret );
        }

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        SIMD_SURVEY_CREATE_PROGRAM_FROM_SOURCE(
            retVal,
            context,
            count,
            strings,
            lengths );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p, program number = %04d",
            retVal,
            pIntercept->getProgramNumber() );

        DUMP_PROGRAM_SOURCE( retVal, singleString, hash );
        SAVE_PROGRAM_HASH( retVal, hash );
        DELETE_COMBINED_PROGRAM_STRING( singleString );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_program CL_API_CALL CLIRN(clCreateProgramWithBinary)(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const size_t* lengths,
    const unsigned char** binaries,
    cl_int* binary_status,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateProgramWithBinary )
    {
        uint64_t    hash = 0;

        COMPUTE_BINARY_HASH( num_devices, lengths, binaries, hash );

        CALL_LOGGING_ENTER( "context = %p, num_devices = %d",
            context,
            num_devices );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_program  retVal = NULL;

        if( pIntercept->config().RejectProgramBinaries )
        {
            if( errcode_ret != NULL )
            {
                errcode_ret[0] = CL_INVALID_BINARY;
            }
        }
        else
        {
            retVal = pIntercept->dispatch().clCreateProgramWithBinary(
                context,
                num_devices,
                device_list,
                lengths,
                binaries,
                binary_status,
                errcode_ret );
        }

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        DUMP_INPUT_PROGRAM_BINARIES(
            retVal,
            num_devices,
            device_list,
            lengths,
            binaries,
            hash );
        SAVE_PROGRAM_HASH( retVal, hash );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_program CL_API_CALL CLIRN(clCreateProgramWithBuiltInKernels)(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* kernel_names,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateProgramWithBuiltInKernels )
    {
        CALL_LOGGING_ENTER( "context = %p, num_devices = %d, kernel_names = [ %s ]",
            context,
            num_devices,
            kernel_names );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_program  retVal = NULL;

        if( ( retVal == NULL ) &&
            pIntercept->config().OverrideBuiltinKernels )
        {
            retVal = pIntercept->createProgramWithBuiltinKernels(
                context );
        }

        if( retVal == NULL )
        {
            retVal = pIntercept->dispatch().clCreateProgramWithBuiltInKernels(
                context,
                num_devices,
                device_list,
                kernel_names,
                errcode_ret);
        }

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clRetainProgram)(
    cl_program program )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clRetainProgram )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetProgramInfo(
                program,
                CL_PROGRAM_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] program = %p",
            ref_count,
            program );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clRetainProgram(
            program );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RETAIN( program );
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetProgramInfo(
                program,
                CL_PROGRAM_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clReleaseProgram)(
    cl_program program )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clReleaseProgram )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetProgramInfo(
                program,
                CL_PROGRAM_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] program = %p",
            ref_count,
            program );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clReleaseProgram(
            program );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RELEASE( program );
        if( pIntercept->callLogging() && ref_count != 0 )
        {
            // This isn't strictly correct, but it's pretty close, and it
            // avoids crashes in some cases for bad implementations.
            --ref_count;
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clBuildProgram)(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    void (CL_CALLBACK *pfn_notify)(cl_program program, void* user_data),
    void* user_data )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clBuildProgram )
    {
        char*   newOptions = NULL;

        SAVE_PROGRAM_OPTIONS_HASH( program, options );
        MODIFY_PROGRAM_OPTIONS( program, options, newOptions );
        DUMP_PROGRAM_OPTIONS( program, options );

        CALL_LOGGING_ENTER( "program = %p, pfn_notify = %p", program, pfn_notify );
        BUILD_LOGGING_INIT();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clBuildProgram(
            program,
            num_devices,
            device_list,
            options,
            pfn_notify,
            user_data );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        BUILD_LOGGING( program, num_devices, device_list );
        SIMD_SURVEY_BUILD_PROGRAM(
            program,
            num_devices,
            device_list,
            options );
        CALL_LOGGING_EXIT( retVal );

        DUMP_OUTPUT_PROGRAM_BINARIES( program );
        DUMP_KERNEL_ISA_BINARIES( program );
        AUTO_CREATE_SPIRV( program, options );
        INCREMENT_PROGRAM_COMPILE_COUNT( program );
        DELETE_MODIFIED_OPTIONS( newOptions );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clCompileProgram)(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    cl_uint num_input_headers,
    const cl_program* input_headers,
    const char** header_include_names,
    void (CL_CALLBACK *pfn_notify)(cl_program program , void* user_data),
    void* user_data )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCompileProgram )
    {
        const bool  modified = false;

        DUMP_PROGRAM_OPTIONS( program, options );

        CALL_LOGGING_ENTER( "program = %p, pfn_notify = %p", program, pfn_notify );
        BUILD_LOGGING_INIT();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clCompileProgram(
            program,
            num_devices,
            device_list,
            options,
            num_input_headers,
            input_headers,
            header_include_names,
            pfn_notify,
            user_data );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        BUILD_LOGGING( program, num_devices, device_list );
        CALL_LOGGING_EXIT( retVal );

        INCREMENT_PROGRAM_COMPILE_COUNT( program );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_program CL_API_CALL CLIRN(clLinkProgram)(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    cl_uint num_input_programs,
    const cl_program* input_programs,
    void (CL_CALLBACK *pfn_notify)(cl_program program, void* user_data),
    void* user_data,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clLinkProgram )
    {
        const bool  modified = false;

        CALL_LOGGING_ENTER( "context = %p, num_input_programs = %u, pfn_notify = %p",
            context,
            num_input_programs,
            pfn_notify );
        CHECK_ERROR_INIT( errcode_ret );
        BUILD_LOGGING_INIT();
        CPU_PERFORMANCE_TIMING_START();

        cl_program  retVal = pIntercept->dispatch().clLinkProgram(
            context,
            num_devices,
            device_list,
            options,
            num_input_programs,
            input_programs,
            pfn_notify,
            user_data,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        BUILD_LOGGING( retVal, num_devices, device_list );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        // TODO: How do we compute a hash for the linked program?
        // This is a new program object, so we don't currently have a hash for it.
        SAVE_PROGRAM_NUMBER( retVal );
        SAVE_PROGRAM_OPTIONS_HASH( retVal, options );
        DUMP_PROGRAM_OPTIONS( retVal, options );
        DUMP_OUTPUT_PROGRAM_BINARIES( retVal );
        DUMP_KERNEL_ISA_BINARIES( retVal );
        INCREMENT_PROGRAM_COMPILE_COUNT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetProgramReleaseCallback)(
    cl_program program,
    void (CL_CALLBACK *pfn_notify)(cl_program program, void* user_data),
    void* user_data )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetProgramReleaseCallback )
    {
        CALL_LOGGING_ENTER( "program = %p", program );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clSetProgramReleaseCallback(
            program,
            pfn_notify,
            user_data );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetProgramSpecializationConstant)(
    cl_program program,
    cl_uint spec_id,
    size_t spec_size,
    const void* spec_value )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetProgramSpecializationConstant )
    {
        CALL_LOGGING_ENTER( "program = %p, spec_id = %u, spec_size = %u",
            program,
            spec_id,
            (cl_uint)spec_size );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clSetProgramSpecializationConstant(
            program,
            spec_id,
            spec_size,
            spec_value );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clUnloadPlatformCompiler)(
    cl_platform_id platform )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clUnloadPlatformCompiler )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clUnloadPlatformCompiler(
            platform );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clUnloadCompiler)( void )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clUnloadCompiler )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clUnloadCompiler();

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetProgramInfo)(
    cl_program program,
    cl_program_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetProgramInfo )
    {
        CALL_LOGGING_ENTER( "param_name = %s (%08X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetProgramInfo(
            program,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetProgramBuildInfo)(
    cl_program program,
    cl_device_id device,
    cl_program_build_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetProgramBuildInfo )
    {
        CALL_LOGGING_ENTER( "param_name = %s (%08X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetProgramBuildInfo(
            program,
            device,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}


///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_kernel CL_API_CALL CLIRN(clCreateKernel)(
    cl_program program,
    const char* kernel_name,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateKernel )
    {
        CALL_LOGGING_ENTER( "program = %p, kernel_name = %s",
            program,
            kernel_name );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_kernel   retVal = NULL;

        if( ( retVal == NULL ) &&
            pIntercept->config().OverrideBuiltinKernels )
        {
            retVal = pIntercept->createBuiltinKernel(
                program,
                kernel_name,
                errcode_ret );
        }

        if( retVal == NULL )
        {
            retVal = pIntercept->dispatch().clCreateKernel(
                program,
                kernel_name,
                errcode_ret );
        }

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        SIMD_SURVEY_CREATE_KERNEL( program, retVal, kernel_name );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        if( retVal != NULL )
        {
            pIntercept->addKernelInfo(
                retVal,
                program,
                kernel_name );
            if( pIntercept->config().KernelInfoLogging ||
                pIntercept->config().PreferredWorkGroupSizeMultipleLogging )
            {
                pIntercept->logKernelInfo(
                    &retVal,
                    1 );
            }
        }

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clCreateKernelsInProgram)(
    cl_program program,
    cl_uint num_kernels,
    cl_kernel* kernels,
    cl_uint* num_kernels_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateKernelsInProgram )
    {
        cl_uint local_num_kernels_ret = 0;

        if( num_kernels_ret == NULL )
        {
            num_kernels_ret = &local_num_kernels_ret;
        }

        CALL_LOGGING_ENTER( "program = %p", program );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clCreateKernelsInProgram(
            program,
            num_kernels,
            kernels,
            num_kernels_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        if( pIntercept->config().LeakChecking &&
            kernels &&
            num_kernels_ret )
        {
            for( cl_uint k = 0; k < num_kernels_ret[0]; k++ )
            {
                ADD_OBJECT_ALLOCATION( kernels[k] );
            }
        }

        std::string retString;
        if( pIntercept->callLogging() )
        {
            pIntercept->getCreateKernelsInProgramRetString(
                retVal,
                kernels,
                num_kernels_ret,
                retString );
        }
        CALL_LOGGING_EXIT( retVal, "%s", retString.c_str() );

        if( ( retVal == CL_SUCCESS ) &&
            ( kernels != NULL ) )
        {
            pIntercept->addKernelInfo(
                kernels,
                program,
                num_kernels_ret[0] );
            if( pIntercept->config().KernelInfoLogging ||
                pIntercept->config().PreferredWorkGroupSizeMultipleLogging )
            {
                pIntercept->logKernelInfo(
                    kernels,
                    num_kernels_ret[0] );
            }
        }

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clRetainKernel)(
    cl_kernel kernel )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clRetainKernel )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetKernelInfo(
                kernel,
                CL_KERNEL_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] kernel = %p",
            ref_count,
            kernel );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clRetainKernel(
            kernel );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RETAIN( kernel );
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetKernelInfo(
                kernel,
                CL_KERNEL_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clReleaseKernel)(
    cl_kernel kernel )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clReleaseKernel )
    {
        pIntercept->removeKernel( kernel );

        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetKernelInfo(
                kernel,
                CL_KERNEL_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] kernel = %p",
            ref_count,
            kernel );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clReleaseKernel(
            kernel );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RELEASE( kernel );
        if( pIntercept->callLogging() && ref_count != 0 )
        {
            // This isn't strictly correct, but it's pretty close, and it
            // avoids crashes in some cases for bad implementations.
            --ref_count;
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetKernelArg)(
    cl_kernel kernel,
    cl_uint arg_index,
    size_t arg_size,
    const void* arg_value )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetKernelArg )
    {
        std::string argsString;
        if( pIntercept->callLogging() )
        {
            pIntercept->getKernelArgString(
                arg_index,
                arg_size,
                arg_value,
                argsString );
        }
        CALL_LOGGING_ENTER_KERNEL(
            kernel,
            "kernel = %p, %s",
            kernel,
            argsString.c_str() );

        if ( pIntercept->config().DumpArgumentsOnSet )
        {
            pIntercept->dumpArgument( kernel, arg_index, arg_size, arg_value );
        }

        SET_KERNEL_ARG( kernel, arg_index, arg_size, arg_value );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clSetKernelArg(
            kernel,
            arg_index,
            arg_size,
            arg_value );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        SIMD_SURVEY_SET_KERNEL_ARG(
            kernel,
            arg_index,
            arg_size,
            arg_value );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetKernelInfo)(
    cl_kernel kernel,
    cl_kernel_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetKernelInfo )
    {
        CALL_LOGGING_ENTER_KERNEL( kernel, "param_name = %s (%X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetKernelInfo(
            kernel,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetKernelArgInfo)(
    cl_kernel kernel,
    cl_uint arg_indx,
    cl_kernel_arg_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetKernelArgInfo )
    {
        CALL_LOGGING_ENTER_KERNEL( kernel, "param_name = %s (%X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetKernelArgInfo(
            kernel,
            arg_indx,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetKernelWorkGroupInfo)(
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_work_group_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetKernelWorkGroupInfo )
    {
        CALL_LOGGING_ENTER_KERNEL( kernel, "param_name = %s (%X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetKernelWorkGroupInfo(
            kernel,
            device,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clWaitForEvents)(
    cl_uint num_events,
    const cl_event* event_list )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clWaitForEvents )
    {
        cl_int  retVal = CL_SUCCESS;

        if( pIntercept->nullEnqueue() == false )
        {
            std::string eventList;
            if( pIntercept->callLogging() )
            {
                pIntercept->getEventListString(
                    num_events,
                    event_list,
                    eventList );
            }
            CALL_LOGGING_ENTER( "event_list = %s",
                eventList.c_str() );
            CHECK_EVENT_LIST( num_events, event_list, NULL );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clWaitForEvents(
                num_events,
                event_list );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            DEVICE_PERFORMANCE_TIMING_CHECK();
        }

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetEventInfo)(
    cl_event event,
    cl_event_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetEventInfo )
    {
        cl_int  retVal = CL_SUCCESS;

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "event = %p, param_name = %s (%08X)",
                event,
                pIntercept->enumName().name( param_name ).c_str(),
                param_name );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clGetEventInfo(
                event,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );
        }

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.1
CL_API_ENTRY cl_event CL_API_CALL CLIRN(clCreateUserEvent)(
    cl_context context,
    cl_int *errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateUserEvent )
    {
        cl_event    retVal = NULL;

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "context = %p",
                context );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clCreateUserEvent(
                context,
                errcode_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );
        }

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clRetainEvent)(
    cl_event event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clRetainEvent )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetEventInfo(
                event,
                CL_EVENT_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] event = %p",
            ref_count,
            event );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clRetainEvent(
            event );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RETAIN( event );
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetEventInfo(
                event,
                CL_EVENT_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clReleaseEvent)(
    cl_event event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clReleaseEvent )
    {
        cl_uint ref_count = 0;
        if( pIntercept->callLogging() )
        {
            ref_count = 0;
            pIntercept->dispatch().clGetEventInfo(
                event,
                CL_EVENT_REFERENCE_COUNT,
                sizeof( ref_count ),
                &ref_count,
                NULL );
        }
        CALL_LOGGING_ENTER( "[ ref count = %d ] event = %p",
            ref_count,
            event );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clReleaseEvent(
            event );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        ADD_OBJECT_RELEASE( event );
        if( pIntercept->callLogging() && ref_count != 0 )
        {
            // This isn't strictly correct, but it's pretty close, and it
            // avoids crashes in some cases for bad implementations.
            --ref_count;
        }
        CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetUserEventStatus)(
    cl_event event,
    cl_int execution_status )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetUserEventStatus )
    {
        CALL_LOGGING_ENTER( "event = %p, status = %s (%d)",
            event,
            pIntercept->enumName().name_command_exec_status( execution_status ).c_str(),
            execution_status );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clSetUserEventStatus(
            event,
            execution_status );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetEventCallback)(
    cl_event event,
    cl_int command_exec_callback_type,
    void (CL_CALLBACK *pfn_notify)( cl_event, cl_int, void * ),
    void *user_data )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetEventCallback )
    {
        CALL_LOGGING_ENTER( "event = %p, callback_type = %s (%d)",
            event,
            pIntercept->enumName().name_command_exec_status( command_exec_callback_type ).c_str(),
            command_exec_callback_type );
        EVENT_CALLBACK_OVERRIDE_INIT( pfn_notify, user_data );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clSetEventCallback(
            event,
            command_exec_callback_type,
            pfn_notify,
            user_data );

        CPU_PERFORMANCE_TIMING_END();
        EVENT_CALLBACK_OVERRIDE_CLEANUP( retVal );
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetEventProfilingInfo)(
    cl_event event,
    cl_profiling_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetEventProfilingInfo )
    {
        cl_int  retVal = CL_SUCCESS;

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "param_name = %s (%08X)",
                pIntercept->enumName().name( param_name ).c_str(),
                param_name );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clGetEventProfilingInfo(
                event,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );
        }

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clFlush)(
    cl_command_queue command_queue )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clFlush )
    {
        CALL_LOGGING_ENTER( "queue = %p", command_queue );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clFlush(
            command_queue );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        DEVICE_PERFORMANCE_TIMING_CHECK();

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clFinish)(
    cl_command_queue command_queue )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clFinish )
    {
        CALL_LOGGING_ENTER( "queue = %p", command_queue );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clFinish(
            command_queue );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        DEVICE_PERFORMANCE_TIMING_CHECK();

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueReadBuffer)(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_read,
    size_t offset,
    size_t cb,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueReadBuffer )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER(
                "queue = %p, buffer = %p, %s, offset = %d, cb = %d, ptr = %p",
                command_queue,
                buffer,
                blocking_read ? "blocking" : "non-blocking",
                offset,
                cb,
                ptr );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            ITT_ADD_PARAM_AS_METADATA( blocking_read );

            if( pIntercept->config().OverrideReadBuffer )
            {
                retVal = pIntercept->ReadBuffer(
                    command_queue,
                    buffer,
                    blocking_read,
                    offset,
                    cb,
                    ptr,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }
            else
            {
                retVal = pIntercept->dispatch().clEnqueueReadBuffer(
                    command_queue,
                    buffer,
                    blocking_read,
                    offset,
                    cb,
                    ptr,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );

            if( blocking_read )
            {
                DEVICE_PERFORMANCE_TIMING_CHECK();
            }
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueReadBufferRect)(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_read,
    const size_t *buffer_origin,
    const size_t *host_origin,
    const size_t *region,
    size_t buffer_row_pitch,
    size_t buffer_slice_pitch,
    size_t host_row_pitch,
    size_t host_slice_pitch,
    void *ptr,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueReadBufferRect )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            if( ( buffer_origin != NULL ) &&
                ( host_origin != NULL ) &&
                ( region != NULL ) )
            {
                CALL_LOGGING_ENTER(
                    "queue = %p, buffer = %p, %s, buffer_origin = < %d, %d, %d >, host_origin = < %d, %d, %d >, region = < %d, %d, %d >, ptr = %p",
                    command_queue,
                    buffer,
                    blocking_read ? "blocking" : "non-blocking",
                    buffer_origin[0], buffer_origin[1], buffer_origin[2],
                    host_origin[0], host_origin[1], host_origin[2],
                    region[0], region[1], region[2],
                    ptr );
            }
            else
            {
                CALL_LOGGING_ENTER(
                    "queue = %p, buffer = %p, %s, ptr = %p",
                    command_queue,
                    buffer,
                    blocking_read ? "blocking" : "non-blocking",
                    ptr );
            }
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            ITT_ADD_PARAM_AS_METADATA( blocking_read );

            retVal = pIntercept->dispatch().clEnqueueReadBufferRect(
                command_queue,
                buffer,
                blocking_read,
                buffer_origin,
                host_origin,
                region,
                buffer_row_pitch,
                buffer_slice_pitch,
                host_row_pitch,
                host_slice_pitch,
                ptr,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );

            if( blocking_read )
            {
                DEVICE_PERFORMANCE_TIMING_CHECK();
            }
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueWriteBuffer)(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_write,
    size_t offset,
    size_t cb,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueWriteBuffer )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER(
                "queue = %p, buffer = %p, %s, offset = %d, cb = %d, ptr = %p",
                command_queue,
                buffer,
                blocking_write ? "blocking" : "non-blocking",
                offset,
                cb,
                ptr );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            ITT_ADD_PARAM_AS_METADATA( blocking_write );

            if( pIntercept->config().OverrideWriteBuffer )
            {
                retVal = pIntercept->WriteBuffer(
                    command_queue,
                    buffer,
                    blocking_write,
                    offset,
                    cb,
                    ptr,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }
            else
            {
                retVal = pIntercept->dispatch().clEnqueueWriteBuffer(
                    command_queue,
                    buffer,
                    blocking_write,
                    offset,
                    cb,
                    ptr,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );

            if( blocking_write )
            {
                DEVICE_PERFORMANCE_TIMING_CHECK();
            }
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueWriteBufferRect)(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_write,
    const size_t *buffer_origin,
    const size_t *host_origin,
    const size_t *region,
    size_t buffer_row_pitch,
    size_t buffer_slice_pitch,
    size_t host_row_pitch,
    size_t host_slice_pitch,
    const void *ptr,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueWriteBufferRect )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            if( ( buffer_origin != NULL ) &&
                ( host_origin != NULL ) &&
                ( region != NULL ) )
            {
                CALL_LOGGING_ENTER(
                    "queue = %p, buffer = %p, %s, buffer_origin = < %d, %d, %d >, host_origin = < %d, %d, %d >, region = < %d, %d, %d >, ptr = %p",
                    command_queue,
                    buffer,
                    blocking_write ? "blocking" : "non-blocking",
                    buffer_origin[0], buffer_origin[1], buffer_origin[2],
                    host_origin[0], host_origin[1], host_origin[2],
                    region[0], region[1], region[2],
                    ptr );
            }
            else
            {
                CALL_LOGGING_ENTER(
                    "queue = %p, buffer = %p, %s, ptr = %p",
                    command_queue,
                    buffer,
                    blocking_write ? "blocking" : "non-blocking",
                    ptr );
            }
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            ITT_ADD_PARAM_AS_METADATA( blocking_write );

            retVal = pIntercept->dispatch().clEnqueueWriteBufferRect(
                command_queue,
                buffer,
                blocking_write,
                buffer_origin,
                host_origin,
                region,
                buffer_row_pitch,
                buffer_slice_pitch,
                host_row_pitch,
                host_slice_pitch,
                ptr,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );

            if( blocking_write )
            {
                DEVICE_PERFORMANCE_TIMING_CHECK();
            }
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueFillBuffer)(
    cl_command_queue command_queue,
    cl_mem buffer,
    const void* pattern,
    size_t pattern_size,
    size_t offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueFillBuffer )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p, buffer = %p, pattern_size = %u, offset = %u, size = %u",
                command_queue,
                buffer,
                (cl_uint)pattern_size,
                (cl_uint)offset,
                (cl_uint)size );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueFillBuffer(
                command_queue,
                buffer,
                pattern,
                pattern_size,
                offset,
                size,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueCopyBuffer)(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    size_t src_offset,
    size_t dst_offset,
    size_t cb,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueCopyBuffer )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER("queue = %p, src_buffer = %p, dst_buffer = %p, src_offset = %u, dst_offset = %u, cb = %u",
                command_queue,
                src_buffer,
                dst_buffer,
                (cl_uint)src_offset,
                (cl_uint)dst_offset,
                (cl_uint)cb );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            if( pIntercept->config().OverrideCopyBuffer )
            {
                retVal = pIntercept->CopyBuffer(
                    command_queue,
                    src_buffer,
                    dst_buffer,
                    src_offset,
                    dst_offset,
                    cb,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }
            else
            {
                retVal = pIntercept->dispatch().clEnqueueCopyBuffer(
                    command_queue,
                    src_buffer,
                    dst_buffer,
                    src_offset,
                    dst_offset,
                    cb,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueCopyBufferRect)(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    const size_t *src_origin,
    const size_t *dst_origin,
    const size_t *region,
    size_t src_row_pitch,
    size_t src_slice_pitch,
    size_t dst_row_pitch,
    size_t dst_slice_pitch,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueCopyBufferRect )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            if( ( src_origin != NULL ) &&
                ( dst_origin != NULL ) &&
                ( region != NULL ) )
            {
                CALL_LOGGING_ENTER(
                    "queue = %p, src_buffer = %p, dst_buffer = %p, src_origin = < %d, %d, %d >, dst_origin = < %d, %d, %d >, region = < %d, %d, %d >",
                    command_queue,
                    src_buffer,
                    dst_buffer,
                    src_origin[0], src_origin[1], src_origin[2],
                    dst_origin[0], dst_origin[1], dst_origin[2],
                    region[0], region[1], region[2] );
            }
            else
            {
                CALL_LOGGING_ENTER(
                    "queue = %p, src_buffer = %p, dst_buffer = %p",
                    command_queue,
                    src_buffer,
                    dst_buffer );
            }
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueCopyBufferRect(
                command_queue,
                src_buffer,
                dst_buffer,
                src_origin,
                dst_origin,
                region,
                src_row_pitch,
                src_slice_pitch,
                dst_row_pitch,
                dst_slice_pitch,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueReadImage)(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_read,
    const size_t* origin,
    const size_t* region,
    size_t row_pitch,
    size_t slice_pitch,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueReadImage )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            if( ( origin != NULL ) &&
                ( region != NULL ) )
            {
                CALL_LOGGING_ENTER(
                    "queue = %p, image = %p, %s, origin = < %d, %d, %d >, region = < %d, %d, %d >, ptr = %p",
                    command_queue,
                    image,
                    blocking_read ? "blocking" : "non-blocking",
                    origin[0], origin[1], origin[2],
                    region[0], region[1], region[2],
                    ptr );
            }
            else
            {
                CALL_LOGGING_ENTER(
                    "queue = %p, image = %p, %s, ptr = %p",
                    command_queue,
                    image,
                    blocking_read ? "blocking" : "non-blocking",
                    ptr );
            }
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            ITT_ADD_PARAM_AS_METADATA( blocking_read );

            if( pIntercept->config().OverrideReadImage )
            {
                retVal = pIntercept->ReadImage(
                    command_queue,
                    image,
                    blocking_read,
                    origin,
                    region,
                    row_pitch,
                    slice_pitch,
                    ptr,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }
            else
            {
                retVal = pIntercept->dispatch().clEnqueueReadImage(
                    command_queue,
                    image,
                    blocking_read,
                    origin,
                    region,
                    row_pitch,
                    slice_pitch,
                    ptr,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );

            if( blocking_read )
            {
                DEVICE_PERFORMANCE_TIMING_CHECK();
            }
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueWriteImage)(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_write,
    const size_t* origin,
    const size_t* region,
    size_t input_row_pitch,
    size_t input_slice_pitch,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueWriteImage )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER(
                "queue = %p, image = %p, %s, ptr = %p",
                command_queue,
                image,
                blocking_write ? "blocking" : "non-blocking",
                ptr );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            ITT_ADD_PARAM_AS_METADATA( blocking_write );

            if( pIntercept->config().OverrideWriteImage )
            {
                retVal = pIntercept->WriteImage(
                    command_queue,
                    image,
                    blocking_write,
                    origin,
                    region,
                    input_row_pitch,
                    input_slice_pitch,
                    ptr,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }
            else
            {
                retVal = pIntercept->dispatch().clEnqueueWriteImage(
                    command_queue,
                    image,
                    blocking_write,
                    origin,
                    region,
                    input_row_pitch,
                    input_slice_pitch,
                    ptr,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );

            if( blocking_write )
            {
                DEVICE_PERFORMANCE_TIMING_CHECK();
            }
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueFillImage)(
    cl_command_queue command_queue,
    cl_mem image,
    const void* fill_color,
    const size_t* origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueFillImage )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p, image = %p",
                command_queue,
                image );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueFillImage(
                command_queue,
                image,
                fill_color,
                origin,
                region,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueCopyImage)(
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_image,
    const size_t* src_origin,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueCopyImage )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p, src_image = %p, dst_image = %p",
                command_queue,
                src_image,
                dst_image );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            if( pIntercept->config().OverrideCopyImage )
            {
                retVal = pIntercept->CopyImage(
                    command_queue,
                    src_image,
                    dst_image,
                    src_origin,
                    dst_origin,
                    region,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }
            else
            {
                retVal = pIntercept->dispatch().clEnqueueCopyImage(
                    command_queue,
                    src_image,
                    dst_image,
                    src_origin,
                    dst_origin,
                    region,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueCopyImageToBuffer)(
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_buffer,
    const size_t* src_origin,
    const size_t* region,
    size_t dst_offset,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueCopyImageToBuffer )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p, src_image = %p, dst_buffer = %p",
                command_queue,
                src_image,
                dst_buffer );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueCopyImageToBuffer(
                command_queue,
                src_image,
                dst_buffer,
                src_origin,
                region,
                dst_offset,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueCopyBufferToImage)(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_image,
    size_t src_offset,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueCopyBufferToImage )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p, src_buffer = %p, dst_image = %p",
                command_queue,
                src_buffer,
                dst_image );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueCopyBufferToImage(
                command_queue,
                src_buffer,
                dst_image,
                src_offset,
                dst_origin,
                region,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY void* CL_API_CALL CLIRN(clEnqueueMapBuffer)(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_map,
    cl_map_flags map_flags,
    size_t offset,
    size_t cb,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueMapBuffer )
    {
        void*   retVal = NULL;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            cl_uint map_count = 0;
            std::string eventWaitListString;
            if( pIntercept->callLogging() )
            {
                map_count = 0;
                pIntercept->dispatch().clGetMemObjectInfo(
                    buffer,
                    CL_MEM_MAP_COUNT,
                    sizeof( map_count ),
                    &map_count,
                    NULL );
                if( num_events_in_wait_list )
                {
                    std::string eventString;
                    pIntercept->getEventListString(
                        num_events_in_wait_list,
                        event_wait_list,
                        eventString );
                    eventWaitListString += ", event_wait_list = ";
                    eventWaitListString += eventString;
                }
            }
            CALL_LOGGING_ENTER(
                "[ map count = %d ] queue = %p, buffer = %p, %s, map_flags = %s (%llX), offset = %d, cb = %d%s",
                map_count,
                command_queue,
                buffer,
                blocking_map ? "blocking" : "non-blocking",
                pIntercept->enumName().name_map_flags( map_flags ).c_str(),
                map_flags,
                offset,
                cb,
                eventWaitListString.c_str() );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            ITT_ADD_PARAM_AS_METADATA( blocking_map );

            retVal = pIntercept->dispatch().clEnqueueMapBuffer(
                command_queue,
                buffer,
                blocking_map,
                map_flags,
                offset,
                cb,
                num_events_in_wait_list,
                event_wait_list,
                event,
                errcode_ret );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            DUMP_BUFFER_AFTER_MAP( command_queue, buffer, blocking_map, map_flags, retVal, offset, cb );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            if( pIntercept->callLogging() )
            {
                map_count = 0;
                pIntercept->dispatch().clGetMemObjectInfo(
                    buffer,
                    CL_MEM_MAP_COUNT,
                    sizeof( map_count ),
                    &map_count,
                    NULL );
            }
            CALL_LOGGING_EXIT_EVENT( errcode_ret[0], event, "[ map count = %d ] returned %p",
                map_count,
                retVal );

            if( blocking_map )
            {
                DEVICE_PERFORMANCE_TIMING_CHECK();
            }
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY void* CL_API_CALL CLIRN(clEnqueueMapImage)(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_map,
    cl_map_flags map_flags,
    const size_t* origin,
    const size_t* region,
    size_t* image_row_pitch,
    size_t* image_slice_pitch,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueMapImage )
    {
        void*   retVal = NULL;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            cl_uint map_count = 0;
            if( pIntercept->callLogging() )
            {
                map_count = 0;
                pIntercept->dispatch().clGetMemObjectInfo(
                    image,
                    CL_MEM_MAP_COUNT,
                    sizeof( map_count ),
                    &map_count,
                    NULL );
            }
            if( ( origin != NULL ) &&
                ( region != NULL ) )
            {
                CALL_LOGGING_ENTER(
                    "[ map count = %d ] queue = %p, image = %p, %s, map_flags = %s (%llX), origin = < %d, %d, %d >, region = < %d, %d, %d >",
                    map_count,
                    command_queue,
                    image,
                    blocking_map ? "blocking" : "non-blocking",
                    pIntercept->enumName().name_map_flags( map_flags ).c_str(),
                    map_flags,
                    origin[0], origin[1], origin[2],
                    region[0], region[1], region[2] );
            }
            else
            {
                CALL_LOGGING_ENTER(
                    "[ map count = %d ] queue = %p, image = %p, %s, map_flags = %s (%llX)",
                    map_count,
                    command_queue,
                    image,
                    blocking_map ? "blocking" : "non-blocking",
                    pIntercept->enumName().name_map_flags( map_flags ).c_str(),
                    map_flags );
            }
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            ITT_ADD_PARAM_AS_METADATA( blocking_map );

            retVal = pIntercept->dispatch().clEnqueueMapImage(
                command_queue,
                image,
                blocking_map,
                map_flags,
                origin,
                region,
                image_row_pitch,
                image_slice_pitch,
                num_events_in_wait_list,
                event_wait_list,
                event,
                errcode_ret );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            if( pIntercept->callLogging() )
            {
                map_count = 0;
                pIntercept->dispatch().clGetMemObjectInfo(
                    image,
                    CL_MEM_MAP_COUNT,
                    sizeof( map_count ),
                    &map_count,
                    NULL );
            }
            CALL_LOGGING_EXIT_EVENT( errcode_ret[0], event, "[ map count = %d ] returned %p",
                map_count,
                retVal );

            if( blocking_map )
            {
                DEVICE_PERFORMANCE_TIMING_CHECK();
            }
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueUnmapMemObject)(
    cl_command_queue command_queue,
    cl_mem memobj,
    void* mapped_ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueUnmapMemObject )
    {
        cl_int  retVal = CL_SUCCESS;

        DUMP_BUFFER_BEFORE_UNMAP( memobj, command_queue );
        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            cl_uint map_count = 0;
            std::string eventWaitListString;
            if( pIntercept->callLogging() )
            {
                map_count = 0;
                pIntercept->dispatch().clGetMemObjectInfo(
                    memobj,
                    CL_MEM_MAP_COUNT,
                    sizeof( map_count ),
                    &map_count,
                    NULL );
                if( num_events_in_wait_list )
                {
                    std::string eventString;
                    pIntercept->getEventListString(
                        num_events_in_wait_list,
                        event_wait_list,
                        eventString );
                    eventWaitListString += ", event_wait_list = ";
                    eventWaitListString += eventString;
                }
            }
            CALL_LOGGING_ENTER(
                "[ map count = %d ] queue = %p, memobj = %p, mapped_ptr = %p%s",
                map_count,
                command_queue,
                memobj,
                mapped_ptr,
                eventWaitListString.c_str() );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueUnmapMemObject(
                command_queue,
                memobj,
                mapped_ptr,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            if( pIntercept->callLogging() )
            {
                map_count = 0;
                pIntercept->dispatch().clGetMemObjectInfo(
                    memobj,
                    CL_MEM_MAP_COUNT,
                    sizeof( map_count ),
                    &map_count,
                    NULL );
            }
            CALL_LOGGING_EXIT_EVENT( retVal, event, "[ map count = %d ]", map_count );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueMigrateMemObjects)(
    cl_command_queue command_queue,
    cl_uint num_mem_objects,
    const cl_mem* mem_objects,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueMigrateMemObjects )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueMigrateMemObjects(
                command_queue,
                num_mem_objects,
                mem_objects,
                flags,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueNDRangeKernel)(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint work_dim,
    const size_t* global_work_offset,
    const size_t* global_work_size,
    const size_t* local_work_size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueNDRangeKernel )
    {
        cl_int  retVal = CL_SUCCESS;

        DUMP_BUFFERS_BEFORE_ENQUEUE( kernel, command_queue );
        DUMP_IMAGES_BEFORE_ENQUEUE( kernel, command_queue );
        CHECK_AUBCAPTURE_START_KERNEL(
            kernel,
            work_dim,
            global_work_size,
            local_work_size,
            command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            if( pIntercept->config().NullLocalWorkSize )
            {
                local_work_size = NULL;
            }
            pIntercept->overrideNullLocalWorkSize(
                work_dim,
                global_work_size,
                local_work_size );

            std::string argsString;
            if( pIntercept->callLogging() )
            {
                pIntercept->getEnqueueNDRangeKernelArgsString(
                    work_dim,
                    global_work_offset,
                    global_work_size,
                    local_work_size,
                    argsString );
                if( num_events_in_wait_list )
                {
                    std::string eventString;
                    pIntercept->getEventListString(
                        num_events_in_wait_list,
                        event_wait_list,
                        eventString );
                    argsString += ", event_wait_list = ";
                    argsString += eventString;
                }
            }
            CALL_LOGGING_ENTER_KERNEL(
                kernel,
                "queue = %p, kernel = %p, %s",
                command_queue,
                kernel,
                argsString.c_str() );

            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            SIMD_SURVEY_NDRANGE_KERNEL(kernel);
            CPU_PERFORMANCE_TIMING_START();

//            ITT_ADD_PARAM_AS_METADATA(command_queue);
//            ITT_ADD_PARAM_AS_METADATA(kernel);
            ITT_ADD_PARAM_AS_METADATA(work_dim);
            ITT_ADD_ARRAY_PARAM_AS_METADATA(work_dim, global_work_offset);
            ITT_ADD_ARRAY_PARAM_AS_METADATA(work_dim, global_work_size);
            ITT_ADD_ARRAY_PARAM_AS_METADATA(work_dim, local_work_size);
            ITT_ADD_ARRAY_PARAM_AS_METADATA(num_events_in_wait_list, event_wait_list);

            if( pIntercept->config().Emulate_cl_intel_unified_shared_memory )
            {
                pIntercept->setUSMKernelExecInfo(
                    command_queue,
                    kernel );
            }

            retVal = CL_INVALID_OPERATION;

            if( ( retVal != CL_SUCCESS ) &&
                pIntercept->config().OverrideBuiltinKernels )
            {

                retVal = pIntercept->NDRangeBuiltinKernel(
                    command_queue,
                    kernel,
                    work_dim,
                    global_work_offset,
                    global_work_size,
                    local_work_size,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }

            if( retVal != CL_SUCCESS )
            {
                retVal = pIntercept->dispatch().clEnqueueNDRangeKernel(
                    command_queue,
                    kernel,
                    work_dim,
                    global_work_offset,
                    global_work_size,
                    local_work_size,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );
            }

            CPU_PERFORMANCE_TIMING_END_KERNEL(kernel);
            DEVICE_PERFORMANCE_TIMING_END_KERNEL(
                command_queue,
                event,
                kernel,
                work_dim,
                global_work_offset,
                global_work_size,
                local_work_size );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        DUMP_BUFFERS_AFTER_ENQUEUE( kernel, command_queue );
        DUMP_IMAGES_AFTER_ENQUEUE( kernel, command_queue );
        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueTask)(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueTask )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START_KERNEL( kernel, 0, NULL, NULL, command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER_KERNEL(
                kernel,
                "queue = %p, kernel = %p",
                command_queue,
                kernel );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueTask(
                command_queue,
                kernel,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END_KERNEL(kernel);
            DEVICE_PERFORMANCE_TIMING_END_KERNEL(
                command_queue,
                event,
                kernel,
                0,
                NULL,
                NULL,
                NULL );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueNativeKernel)(
    cl_command_queue command_queue,
    void (CL_CALLBACK *user_func)(void *),
    void* args,
    size_t cb_args,
    cl_uint num_mem_objects,
    const cl_mem* mem_list,
    const void** args_mem_loc,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueNativeKernel )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueNativeKernel(
                command_queue,
                user_func,
                args,
                cb_args,
                num_mem_objects,
                mem_list,
                args_mem_loc,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueMarker)(
    cl_command_queue command_queue,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueMarker )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueMarker(
                command_queue,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueWaitForEvents)(
    cl_command_queue command_queue,
    cl_uint num_events,
    const cl_event* event_list )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueWaitForEvents )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            std::string eventWaitListString;
            if( pIntercept->callLogging() &&
                num_events )
            {
                std::string eventString;
                pIntercept->getEventListString(
                    num_events,
                    event_list,
                    eventString );
                eventWaitListString += ", event_list = ";
                eventWaitListString += eventString;
            }
            CALL_LOGGING_ENTER( "queue = %p%s",
                command_queue,
                eventWaitListString.c_str() );
            CHECK_EVENT_LIST( num_events, event_list, NULL );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueWaitForEvents(
                command_queue,
                num_events,
                event_list );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            DEVICE_PERFORMANCE_TIMING_CHECK();
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueBarrier)(
    cl_command_queue command_queue )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueBarrier )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueBarrier(
                command_queue );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        FLUSH_AFTER_ENQUEUE_BARRIER( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueMarkerWithWaitList)(
    cl_command_queue command_queue,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueMarkerWithWaitList )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            std::string eventWaitListString;
            if( pIntercept->callLogging() &&
                num_events_in_wait_list )
            {
                std::string eventString;
                pIntercept->getEventListString(
                    num_events_in_wait_list,
                    event_wait_list,
                    eventString );
                eventWaitListString += ", event_wait_list = ";
                eventWaitListString += eventString;
            }
            CALL_LOGGING_ENTER( "queue = %p%s",
                command_queue,
                eventWaitListString.c_str() );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueMarkerWithWaitList(
                command_queue,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueBarrierWithWaitList)(
    cl_command_queue command_queue,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueBarrierWithWaitList )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            std::string eventWaitListString;
            if( pIntercept->callLogging() &&
                num_events_in_wait_list )
            {
                std::string eventString;
                pIntercept->getEventListString(
                    num_events_in_wait_list,
                    event_wait_list,
                    eventString );
                eventWaitListString += ", event_wait_list = ";
                eventWaitListString += eventString;
            }
            CALL_LOGGING_ENTER( "queue = %p%s",
                command_queue,
                eventWaitListString.c_str() );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueBarrierWithWaitList(
                command_queue,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        FLUSH_AFTER_ENQUEUE_BARRIER( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY void* CL_API_CALL CLIRN(clGetExtensionFunctionAddress)(
    const char* func_name )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetExtensionFunctionAddress )
    {
        CALL_LOGGING_ENTER( "func_name = %s", func_name ? func_name : "(NULL)" );
        CPU_PERFORMANCE_TIMING_START();

        void*   retVal = NULL;
        if( func_name != NULL )
        {
            // First, check to see if this is an extension we know about.
            if( retVal == NULL )
            {
                retVal = pIntercept->getExtensionFunctionAddress(
                    NULL,
                    func_name );
            }

            // If it's not, call into the dispatch table as usual.
            if( retVal == NULL )
            {
                retVal = pIntercept->dispatch().clGetExtensionFunctionAddress(
                    func_name );
            }
        }

        CPU_PERFORMANCE_TIMING_END();
        CALL_LOGGING_EXIT( CL_SUCCESS, "returned %p", retVal );

        return retVal;
    }
    else
    {
        return NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY void* CL_API_CALL CLIRN(clGetExtensionFunctionAddressForPlatform)(
    cl_platform_id platform,
    const char* func_name )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetExtensionFunctionAddressForPlatform )
    {
        std::string platformInfo;
        if( pIntercept->callLogging() )
        {
            pIntercept->getPlatformInfoString(
                platform,
                platformInfo );
        }
        CALL_LOGGING_ENTER( "platform = [ %s ], func_name = %s",
            platformInfo.c_str(),
            func_name ? func_name : "(NULL)" );
        CPU_PERFORMANCE_TIMING_START();

        void*   retVal = NULL;
        if( func_name != NULL )
        {
            // First, check to see if this is an extension we know about.
            if( retVal == NULL )
            {
                retVal = pIntercept->getExtensionFunctionAddress(
                    platform,
                    func_name );
            }

            // If it's not, call into the dispatch table as usual.
            if( retVal == NULL )
            {
                retVal = pIntercept->dispatch().clGetExtensionFunctionAddressForPlatform(
                    platform,
                    func_name );
            }
        }

        CPU_PERFORMANCE_TIMING_END();
        CALL_LOGGING_EXIT( CL_SUCCESS, "returned %p", retVal );

        return retVal;
    }
    else
    {
        return NULL;
    }
}

// CL-GL Sharing

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateFromGLBuffer)(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint bufobj,
    int* errcode_ret)   // Not cl_int*?
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromGLBuffer )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromGLBuffer(
                context,
                flags,
                bufobj,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_BUFFER( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 1.2
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateFromGLTexture)(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromGLTexture )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX), "
                "texture_target = %s (%d), "
                "miplevel = %d, "
                "texture = %d",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags,
                pIntercept->enumName().name_gl( target ).c_str(),
                target,
                miplevel,
                texture );

            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromGLTexture(
                context,
                flags,
                target,
                miplevel,
                texture,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );

            pIntercept->logCL_GLTextureDetails( retVal, target, miplevel, texture );

            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateFromGLTexture2D)(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromGLTexture2D )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX), "
                "texture_target = %s (%d), "
                "miplevel = %d, "
                "texture = %d",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags,
                pIntercept->enumName().name_gl( target ).c_str(),
                target,
                miplevel,
                texture );

            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromGLTexture2D(
                context,
                flags,
                target,
                miplevel,
                texture,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );

            pIntercept->logCL_GLTextureDetails( retVal, target, miplevel, texture );

            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateFromGLTexture3D)(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromGLTexture3D )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX), "
                "texture_target = %s (%d), "
                "miplevel = %d, "
                "texture = %d",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags,
                pIntercept->enumName().name_gl( target ).c_str(),
                target,
                miplevel,
                texture );

            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromGLTexture3D(
                context,
                flags,
                target,
                miplevel,
                texture,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );

            pIntercept->logCL_GLTextureDetails( retVal, target, miplevel, texture );

            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreateFromGLRenderbuffer)(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint renderbuffer,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromGLRenderbuffer )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromGLRenderbuffer(
                context,
                flags,
                renderbuffer,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetGLObjectInfo)(
    cl_mem memobj,
    cl_gl_object_type* gl_object_type,
    cl_GLuint* gl_object_name)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(memobj);
        if( dispatchX.clGetGLObjectInfo )
        {
            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetGLObjectInfo(
                memobj,
                gl_object_type,
                gl_object_name);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetGLTextureInfo)(
    cl_mem memobj,
    cl_gl_texture_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(memobj);
        if( dispatchX.clGetGLTextureInfo )
        {
            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetGLTextureInfo(
                memobj,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueAcquireGLObjects)(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueAcquireGLObjects )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER( "queue = %p",
                    command_queue );
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueAcquireGLObjects(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueReleaseGLObjects)(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueReleaseGLObjects )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER( "queue = %p",
                    command_queue );
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueReleaseGLObjects(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            DEVICE_PERFORMANCE_TIMING_CHECK();

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY void* CL_API_CALL CLIRN(clSVMAlloc) (
    cl_context context,
    cl_svm_mem_flags flags,
    size_t size,
    cl_uint alignment)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSVMAlloc )
    {
        CALL_LOGGING_ENTER( "flags = %s (%llX), size = %d, alignment = %d",
            pIntercept->enumName().name_svm_mem_flags( flags ).c_str(),
            flags,
            size,
            alignment );
        CPU_PERFORMANCE_TIMING_START();

        void*   retVal = pIntercept->dispatch().clSVMAlloc(
            context,
            flags,
            size,
            alignment );

        CPU_PERFORMANCE_TIMING_END();
        ADD_SVM_ALLOCATION( retVal, size );
        // There is no error code returned from clSVMAlloc(), so strictly
        // speaking we have no error to "check" here.  Still, we'll invent
        // one if clSVMAlloc() returned NULL, so something will get logged
        // if ErrorLogging is enabled.
        cl_int  errorCode = ( retVal != NULL ) ? CL_SUCCESS : CL_INVALID_OPERATION;
        CHECK_ERROR( errorCode );
        CALL_LOGGING_EXIT( errorCode, "returned %p", retVal );

        return retVal;
    }

    cl_int* errcode_ret = NULL;
    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY void CL_API_CALL CLIRN(clSVMFree) (
    cl_context context,
    void* svm_pointer)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSVMFree )
    {
        CALL_LOGGING_ENTER( "svm_pointer = %p",
            svm_pointer );
        CPU_PERFORMANCE_TIMING_START();

        pIntercept->dispatch().clSVMFree(
            context,
            svm_pointer );

        CPU_PERFORMANCE_TIMING_END();
        REMOVE_SVM_ALLOCATION( svm_pointer );
        CALL_LOGGING_EXIT( CL_SUCCESS );
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueSVMFree) (
    cl_command_queue command_queue,
    cl_uint num_svm_pointers,
    void* svm_pointers [],
    void (CL_CALLBACK* pfn_free_func)(
            cl_command_queue queue,
            cl_uint num_svm_pointers,
            void* svm_pointers [],
            void* user_data ),
    void* user_data,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueSVMFree )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueSVMFree(
                command_queue,
                num_svm_pointers,
                svm_pointers,
                pfn_free_func,
                user_data,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueSVMMemcpy) (
    cl_command_queue command_queue,
    cl_bool blocking_copy,
    void* dst_ptr,
    const void* src_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueSVMMemcpy )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueSVMMemcpy(
                command_queue,
                blocking_copy,
                dst_ptr,
                src_ptr,
                size,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueSVMMemFill) (
    cl_command_queue command_queue,
    void* svm_ptr,
    const void* pattern,
    size_t pattern_size,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueSVMMemFill )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p, svm_ptr = %p, pattern_size = %u, size = %u",
                command_queue,
                svm_ptr,
                (cl_uint)pattern_size,
                (cl_uint)size );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueSVMMemFill(
                command_queue,
                svm_ptr,
                pattern,
                pattern_size,
                size,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueSVMMap) (
    cl_command_queue command_queue,
    cl_bool blocking_map,
    cl_map_flags map_flags,
    void* svm_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueSVMMap )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueSVMMap(
                command_queue,
                blocking_map,
                map_flags,
                svm_ptr,
                size,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clEnqueueSVMUnmap) (
    cl_command_queue command_queue,
    void* svm_ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueSVMUnmap )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueSVMUnmap(
                command_queue,
                svm_ptr,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
        CHECK_AUBCAPTURE_STOP( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetKernelArgSVMPointer) (
    cl_kernel kernel,
    cl_uint arg_index,
    const void* arg_value)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetKernelArgSVMPointer )
    {
        CALL_LOGGING_ENTER_KERNEL(
            kernel,
            "kernel = %p, index = %d, value = %p",
            kernel,
            arg_index,
            arg_value );
        SET_KERNEL_ARG_SVM_POINTER( kernel, arg_index, arg_value );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clSetKernelArgSVMPointer(
            kernel,
            arg_index,
            arg_value );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetKernelExecInfo) (
    cl_kernel kernel,
    cl_kernel_exec_info param_name,
    size_t param_value_size,
    const void* param_value)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetKernelExecInfo )
    {
        CALL_LOGGING_ENTER_KERNEL( kernel, "param_name = %s (%08X)",
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = CL_INVALID_OPERATION;

        if( pIntercept->config().Emulate_cl_intel_unified_shared_memory )
        {
            retVal = pIntercept->trackUSMKernelExecInfo(
                kernel,
                param_name,
                param_value_size,
                param_value );
        }

        if( retVal != CL_SUCCESS )
        {
            retVal = pIntercept->dispatch().clSetKernelExecInfo(
                kernel,
                param_name,
                param_value_size,
                param_value );
        }

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_mem CL_API_CALL CLIRN(clCreatePipe) (
    cl_context context,
    cl_mem_flags flags,
    cl_uint pipe_packet_size,
    cl_uint pipe_max_packets,
    const cl_pipe_properties* properties,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreatePipe )
    {
        CALL_LOGGING_ENTER( "context = %p, flags = %s (%llX), pipe_packet_size = %u, pipe_max_packets = %u",
            context,
            pIntercept->enumName().name_mem_flags( flags ).c_str(),
            flags,
            pipe_packet_size,
            pipe_max_packets );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_mem  retVal = pIntercept->dispatch().clCreatePipe(
            context,
            flags,
            pipe_packet_size,
            pipe_max_packets,
            properties,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0] );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetPipeInfo) (
    cl_mem pipe,
    cl_pipe_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetPipeInfo )
    {
        CALL_LOGGING_ENTER( "mem = %p, param_name = %s (%08X)",
            pipe,
            pIntercept->enumName().name( param_name ).c_str(),
            param_name );
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetPipeInfo(
            pipe,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_command_queue CL_API_CALL CLIRN(clCreateCommandQueueWithProperties) (
    cl_context context,
    cl_device_id device,
    const cl_queue_properties* properties,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateCommandQueueWithProperties )
    {
        cl_queue_properties*    newProperties = NULL;
        cl_command_queue    retVal = NULL;

        std::string deviceInfo;
        std::string commandQueueProperties;
        if( pIntercept->callLogging() )
        {
            pIntercept->getDeviceInfoString(
                1,
                &device,
                deviceInfo );
            pIntercept->getCommandQueuePropertiesString(
                properties,
                commandQueueProperties );
        }
        CALL_LOGGING_ENTER( "context = %p, device = [ %s ], properties = [ %s ]",
            context,
            deviceInfo.c_str(),
            commandQueueProperties.c_str() );
        CREATE_COMMAND_QUEUE_OVERRIDE_INIT( device, properties, newProperties );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

#if defined(USE_MDAPI)
        if( pIntercept->config().DevicePerfCounterEventBasedSampling )
        {
            if( ( retVal == NULL ) && newProperties )
            {
                retVal = pIntercept->createMDAPICommandQueue(
                    context,
                    device,
                    newProperties,
                    errcode_ret );
            }
            if( retVal == NULL )
            {
                retVal = pIntercept->createMDAPICommandQueue(
                    context,
                    device,
                    properties,
                    errcode_ret );
            }
        }
#endif

        if( ( retVal == NULL ) && newProperties )
        {
            retVal = pIntercept->dispatch().clCreateCommandQueueWithProperties(
                context,
                device,
                newProperties,
                errcode_ret );
        }
        if( retVal == NULL )
        {
            retVal = pIntercept->dispatch().clCreateCommandQueueWithProperties(
                context,
                device,
                properties,
                errcode_ret );
        }

        CPU_PERFORMANCE_TIMING_END();
        CREATE_COMMAND_QUEUE_OVERRIDE_CLEANUP( newProperties );
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_create_command_queue
// This function should stay in sync with clCreateCommandQueueWithProperties, above.
CL_API_ENTRY cl_command_queue CL_API_CALL clCreateCommandQueueWithPropertiesKHR(
    cl_context context,
    cl_device_id device,
    const cl_queue_properties_khr* properties,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(device);
        if( dispatchX.clCreateCommandQueueWithPropertiesKHR )
        {
            cl_queue_properties*    newProperties = NULL;
            cl_command_queue    retVal = NULL;

            std::string deviceInfo;
            std::string commandQueueProperties;
            if( pIntercept->callLogging() )
            {
                pIntercept->getDeviceInfoString(
                    1,
                    &device,
                    deviceInfo );
                pIntercept->getCommandQueuePropertiesString(
                    properties,
                    commandQueueProperties );
            }
            CALL_LOGGING_ENTER( "context = %p, device = [ %s ], properties = [ %s ]",
                context,
                deviceInfo.c_str(),
                commandQueueProperties.c_str() );
            CREATE_COMMAND_QUEUE_OVERRIDE_INIT( device, properties, newProperties );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

#if defined(USE_MDAPI)
            if( pIntercept->config().DevicePerfCounterEventBasedSampling )
            {
                if( ( retVal == NULL ) && newProperties )
                {
                    retVal = pIntercept->createMDAPICommandQueue(
                        context,
                        device,
                        newProperties,
                        errcode_ret );
                }
                if( retVal == NULL )
                {
                    retVal = pIntercept->createMDAPICommandQueue(
                        context,
                        device,
                        properties,
                        errcode_ret );
                }
            }
#endif

            if( ( retVal == NULL ) && newProperties )
            {
                retVal = dispatchX.clCreateCommandQueueWithPropertiesKHR(
                    context,
                    device,
                    newProperties,
                    errcode_ret );
            }
            if( retVal == NULL )
            {
                retVal = dispatchX.clCreateCommandQueueWithPropertiesKHR(
                    context,
                    device,
                    properties,
                    errcode_ret );
            }

            CPU_PERFORMANCE_TIMING_END();
            CREATE_COMMAND_QUEUE_OVERRIDE_CLEANUP( newProperties );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.0
CL_API_ENTRY cl_sampler CL_API_CALL CLIRN(clCreateSamplerWithProperties) (
    cl_context context,
    const cl_sampler_properties* sampler_properties,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateSamplerWithProperties )
    {
        std::string samplerProperties;
        if( pIntercept->callLogging() )
        {
            pIntercept->getSamplerPropertiesString(
                sampler_properties,
                samplerProperties );
        }
        CALL_LOGGING_ENTER( "context = %p, properties = [ %s ]",
            context,
            samplerProperties.c_str() );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_sampler  retVal = pIntercept->dispatch().clCreateSamplerWithProperties(
            context,
            sampler_properties,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );
        ADD_SAMPLER( retVal, samplerProperties );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clSetDefaultDeviceCommandQueue) (
    cl_context context,
    cl_device_id device,
    cl_command_queue command_queue )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clSetDefaultDeviceCommandQueue )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clSetDefaultDeviceCommandQueue(
            context,
            device,
            command_queue );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetDeviceAndHostTimer) (
    cl_device_id device,
    cl_ulong* device_timestamp,
    cl_ulong* host_timestamp )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetDeviceAndHostTimer )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetDeviceAndHostTimer(
            device,
            device_timestamp,
            host_timestamp );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetHostTimer) (
    cl_device_id device,
    cl_ulong* host_timestamp )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetHostTimer )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetHostTimer(
            device,
            host_timestamp );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.1
CL_API_ENTRY cl_program CL_API_CALL CLIRN(clCreateProgramWithIL) (
    cl_context context,
    const void* il,
    size_t length,
    cl_int *errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCreateProgramWithIL )
    {
        char*       injectedSPIRV = NULL;
        uint64_t    hash = 0;

        COMPUTE_SPIRV_HASH( length, il, hash );
        INJECT_PROGRAM_SPIRV( length, il, injectedSPIRV, hash );

        CALL_LOGGING_ENTER( "context = %p, length = %u",
            context,
            (cl_uint)length );
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_program  retVal = pIntercept->dispatch().clCreateProgramWithIL(
            context,
            il,
            length,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        ADD_OBJECT_ALLOCATION( retVal );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        DUMP_PROGRAM_SPIRV( retVal, length, il, hash );
        SAVE_PROGRAM_HASH( retVal, hash );
        DELETE_INJECTED_SPIRV( injectedSPIRV );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_il_program
// This function should stay in sync with clCreateProgramWithIL, above.
CL_API_ENTRY cl_program CL_API_CALL clCreateProgramWithILKHR(
    cl_context context,
    const void* il,
    size_t length,
    cl_int *errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateProgramWithILKHR )
        {
            char*       injectedSPIRV = NULL;
            uint64_t    hash = 0;

            COMPUTE_SPIRV_HASH( length, il, hash );
            INJECT_PROGRAM_SPIRV( length, il, injectedSPIRV, hash );

            CALL_LOGGING_ENTER( "context = %p, length = %u",
                context,
                length );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_program  retVal = dispatchX.clCreateProgramWithILKHR(
                context,
                il,
                length,
                errcode_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            DUMP_PROGRAM_SPIRV( retVal, length, il, hash );
            SAVE_PROGRAM_HASH( retVal, hash );
            DELETE_INJECTED_SPIRV( injectedSPIRV );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.1
CL_API_ENTRY cl_kernel CL_API_CALL CLIRN(clCloneKernel) (
    cl_kernel source_kernel,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clCloneKernel )
    {
        CALL_LOGGING_ENTER();
        CHECK_ERROR_INIT( errcode_ret );
        CPU_PERFORMANCE_TIMING_START();

        cl_kernel   retVal = pIntercept->dispatch().clCloneKernel(
            source_kernel,
            errcode_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( errcode_ret[0] );
        CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.1
CL_API_ENTRY cl_int CL_API_CALL CLIRN(clGetKernelSubGroupInfo) (
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_sub_group_info param_name,
    size_t input_value_size,
    const void* input_value,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clGetKernelSubGroupInfo )
    {
        cl_int  retVal = CL_SUCCESS;

        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        retVal = pIntercept->dispatch().clGetKernelSubGroupInfo(
            kernel,
            device,
            param_name,
            input_value_size,
            input_value,
            param_value_size,
            param_value,
            param_value_size_ret );

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_subgroups
// This function should stay in sync with clGetKernelSubGroupInfo, above.
CL_API_ENTRY cl_int CL_API_CALL clGetKernelSubGroupInfoKHR(
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_sub_group_info param_name,
    size_t input_value_size,
    const void* input_value,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(kernel);
        if( dispatchX.clGetKernelSubGroupInfoKHR )
        {
            cl_int  retVal = CL_SUCCESS;

            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            retVal = dispatchX.clGetKernelSubGroupInfoKHR(
                kernel,
                device,
                param_name,
                input_value_size,
                input_value,
                param_value_size,
                param_value,
                param_value_size_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// OpenCL 2.1
CL_API_ENTRY cl_int CL_API_CALL clEnqueueSVMMigrateMem(
    cl_command_queue command_queue,
    cl_uint num_svm_pointers,
    const void** svm_pointers,
    const size_t* sizes,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept && pIntercept->dispatch().clEnqueueSVMMigrateMem )
    {
        cl_int  retVal = CL_SUCCESS;

        CHECK_AUBCAPTURE_START( command_queue );

        if( pIntercept->nullEnqueue() == false )
        {
            CALL_LOGGING_ENTER( "queue = %p",
                command_queue );
            CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
            DEVICE_PERFORMANCE_TIMING_START( event );
            CPU_PERFORMANCE_TIMING_START();

            retVal = pIntercept->dispatch().clEnqueueSVMMigrateMem(
                command_queue,
                num_svm_pointers,
                svm_pointers,
                sizes,
                flags,
                num_events_in_wait_list,
                event_wait_list,
                event );

            CPU_PERFORMANCE_TIMING_END();
            DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
            CHECK_ERROR( retVal );
            ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
            CALL_LOGGING_EXIT_EVENT( retVal, event );
        }

        FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_gl_sharing
CL_API_ENTRY cl_int CL_API_CALL clGetGLContextInfoKHR(
    const cl_context_properties *properties,
    cl_gl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    // clGetGLContextInfoKHR is a special-case.
    // It's an extension function and is part of cl_khr_gl_sharing, but it
    // doesn't necessarily pass a dispatchable object as its first argument,
    // and is implemented in the ICD loader and called into via the core API
    // dispatch table.  This means that we can install it into our core API
    // dispatch table as well, and don't need to look it up per-platform.

    if( pIntercept && pIntercept->dispatch().clGetGLContextInfoKHR )
    {
        CALL_LOGGING_ENTER();
        CPU_PERFORMANCE_TIMING_START();

        cl_int  retVal = pIntercept->dispatch().clGetGLContextInfoKHR(
            properties,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);

        CPU_PERFORMANCE_TIMING_END();
        CHECK_ERROR( retVal );
        CALL_LOGGING_EXIT( retVal );

        return retVal;
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_gl_event
CL_API_ENTRY cl_event CL_API_CALL clCreateEventFromGLsyncKHR(
    cl_context context,
    cl_GLsync sync,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateEventFromGLsyncKHR )
        {
            CALL_LOGGING_ENTER( "context = %p",
                context );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_event    retVal = dispatchX.clCreateEventFromGLsyncKHR(
                context,
                sync,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

#if defined(_WIN32)

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d10_sharing
CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDsFromD3D10KHR(
    cl_platform_id platform,
    cl_d3d10_device_source_khr d3d_device_source,
    void* d3d_object,
    cl_d3d10_device_set_khr d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(platform);
        if( dispatchX.clGetDeviceIDsFromD3D10KHR )
        {
            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetDeviceIDsFromD3D10KHR(
                platform,
                d3d_device_source,
                d3d_object,
                d3d_device_set,
                num_entries,
                devices,
                num_devices);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d10_sharing
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D10BufferKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Buffer* resource,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromD3D10BufferKHR )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromD3D10BufferKHR(
                context,
                flags,
                resource,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_BUFFER( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d10_sharing
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D10Texture2DKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Texture2D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromD3D10Texture2DKHR )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromD3D10Texture2DKHR(
                context,
                flags,
                resource,
                subresource,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d10_sharing
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D10Texture3DKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Texture3D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromD3D10Texture3DKHR )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromD3D10Texture3DKHR(
                context,
                flags,
                resource,
                subresource,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d10_sharing
CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireD3D10ObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueAcquireD3D10ObjectsKHR )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueAcquireD3D10ObjectsKHR(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d10_sharing
CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseD3D10ObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueReleaseD3D10ObjectsKHR )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueReleaseD3D10ObjectsKHR(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            DEVICE_PERFORMANCE_TIMING_CHECK();

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d11_sharing
CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDsFromD3D11KHR(
    cl_platform_id platform,
    cl_d3d11_device_source_khr d3d_device_source,
    void* d3d_object,
    cl_d3d11_device_set_khr d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(platform);
        if( dispatchX.clGetDeviceIDsFromD3D11KHR )
        {
            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetDeviceIDsFromD3D11KHR(
                platform,
                d3d_device_source,
                d3d_object,
                d3d_device_set,
                num_entries,
                devices,
                num_devices);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d11_sharing
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D11BufferKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Buffer* resource,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromD3D11BufferKHR )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromD3D11BufferKHR(
                context,
                flags,
                resource,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_BUFFER( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d11_sharing
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D11Texture2DKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Texture2D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromD3D11Texture2DKHR )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromD3D11Texture2DKHR(
                context,
                flags,
                resource,
                subresource,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d11_sharing
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D11Texture3DKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Texture3D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromD3D11Texture3DKHR )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromD3D11Texture3DKHR(
                context,
                flags,
                resource,
                subresource,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d11_sharing
CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireD3D11ObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueAcquireD3D11ObjectsKHR )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueAcquireD3D11ObjectsKHR(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_d3d11_sharing
CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseD3D11ObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueReleaseD3D11ObjectsKHR )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueReleaseD3D11ObjectsKHR(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            DEVICE_PERFORMANCE_TIMING_CHECK();

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_dx9_media_sharing
CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDsFromDX9MediaAdapterKHR(
    cl_platform_id platform,
    cl_uint num_media_adapters,
    cl_dx9_media_adapter_type_khr* media_adapters_type,
    void* media_adapters,
    cl_dx9_media_adapter_set_khr media_adapter_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(platform);
        if( dispatchX.clGetDeviceIDsFromDX9MediaAdapterKHR )
        {
            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetDeviceIDsFromDX9MediaAdapterKHR(
                platform,
                num_media_adapters,
                media_adapters_type,
                media_adapters,
                media_adapter_set,
                num_entries,
                devices,
                num_devices);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_dx9_media_sharing
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromDX9MediaSurfaceKHR(
    cl_context context,
    cl_mem_flags flags,
    cl_dx9_media_adapter_type_khr adapter_type,
    void* surface_info,
    cl_uint plane,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromDX9MediaSurfaceKHR )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromDX9MediaSurfaceKHR(
                context,
                flags,
                adapter_type,
                surface_info,
                plane,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_dx9_media_sharing
CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireDX9MediaSurfacesKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueAcquireDX9MediaSurfacesKHR )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueAcquireDX9MediaSurfacesKHR(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_khr_dx9_media_sharing
CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseDX9MediaSurfacesKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueReleaseDX9MediaSurfacesKHR )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueReleaseDX9MediaSurfacesKHR(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            DEVICE_PERFORMANCE_TIMING_CHECK();

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}
#endif

#if defined(_WIN32)
///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_dx9_media_sharing Extension
CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDsFromDX9INTEL(
    cl_platform_id platform,
    cl_dx9_device_source_intel d3d_device_source,
    void *dx9_object,
    cl_dx9_device_set_intel d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(platform);
        if( dispatchX.clGetDeviceIDsFromDX9INTEL )
        {
            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetDeviceIDsFromDX9INTEL(
                platform,
                d3d_device_source,
                dx9_object,
                d3d_device_set,
                num_entries,
                devices,
                num_devices);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_dx9_media_sharing Extension
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromDX9MediaSurfaceINTEL(
    cl_context context,
    cl_mem_flags flags,
    IDirect3DSurface9* resource,
    HANDLE sharedHandle,
    UINT plane,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromDX9MediaSurfaceINTEL )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromDX9MediaSurfaceINTEL(
                context,
                flags,
                resource,
                sharedHandle,
                plane,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_dx9_media_sharing Extension
CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireDX9ObjectsINTEL(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueAcquireDX9ObjectsINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueAcquireDX9ObjectsINTEL(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_dx9_media_sharing Extension
CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseDX9ObjectsINTEL(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueReleaseDX9ObjectsINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueReleaseDX9ObjectsINTEL(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            DEVICE_PERFORMANCE_TIMING_CHECK();

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Unofficial MDAPI extension:
CL_API_ENTRY cl_command_queue CL_API_CALL clCreatePerfCountersCommandQueueINTEL(
    cl_context context,
    cl_device_id device,
    cl_command_queue_properties properties,
    cl_uint configuration,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreatePerfCountersCommandQueueINTEL )
        {
            // We don't have to do this, since profiling must be enabled
            // for a perf counters command queue, but it doesn't hurt to
            // add it, either.
            if( pIntercept->config().DevicePerformanceTiming ||
                pIntercept->config().ITTPerformanceTiming ||
                pIntercept->config().ChromePerformanceTiming ||
                pIntercept->config().SIMDSurvey ||
                pIntercept->config().DevicePerfCounterEventBasedSampling )
            {
                properties |= (cl_command_queue_properties)CL_QUEUE_PROFILING_ENABLE;
            }

            CALL_LOGGING_ENTER( "context = %p",
                context );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_command_queue    retVal = dispatchX.clCreatePerfCountersCommandQueueINTEL(
                context,
                device,
                properties,
                configuration,
                errcode_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            ITT_REGISTER_COMMAND_QUEUE( retVal, true );
            CHROME_REGISTER_COMMAND_QUEUE( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// Unofficial MDAPI extension:
CL_API_ENTRY cl_int CL_API_CALL clSetPerformanceConfigurationINTEL(
    cl_device_id    device,
    cl_uint         count,
    cl_uint*        offsets,
    cl_uint*        values )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(device);
        if( dispatchX.clSetPerformanceConfigurationINTEL )
        {
            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            cl_int retVal = dispatchX.clSetPerformanceConfigurationINTEL(
                device,
                count,
                offsets,
                values );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_accelerator
CL_API_ENTRY cl_accelerator_intel CL_API_CALL clCreateAcceleratorINTEL(
    cl_context context,
    cl_accelerator_type_intel accelerator_type,
    size_t descriptor_size,
    const void* descriptor,
    cl_int* errcode_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateAcceleratorINTEL )
        {
            if( ( accelerator_type == CL_ACCELERATOR_TYPE_MOTION_ESTIMATION_INTEL ) &&
                ( descriptor_size >= sizeof( cl_motion_estimation_desc_intel ) ) )
            {
                cl_motion_estimation_desc_intel* desc =
                    (cl_motion_estimation_desc_intel*)descriptor;
                CALL_LOGGING_ENTER( "context = %p, motion_estimation_desc[ mb_block_type = %d, subpixel_mode = %d, sad_adjust_mode = %d, search_path_type = %d ]",
                    context,
                    desc->mb_block_type,
                    desc->subpixel_mode,
                    desc->sad_adjust_mode,
                    desc->search_path_type );
            }
            else
            {
                CALL_LOGGING_ENTER( "context = %p, accelerator_type = %u",
                    context,
                    (cl_uint)accelerator_type );
            }
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_accelerator_intel retVal = dispatchX.clCreateAcceleratorINTEL(
                context,
                accelerator_type,
                descriptor_size,
                descriptor,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( errcode_ret[0] );
            //ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_accelerator
CL_API_ENTRY cl_int CL_API_CALL clGetAcceleratorInfoINTEL(
    cl_accelerator_intel accelerator,
    cl_accelerator_info_intel param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(accelerator);
        if( dispatchX.clGetAcceleratorInfoINTEL )
        {
            CALL_LOGGING_ENTER( "param_name = %s (%X)",
                pIntercept->enumName().name( param_name ).c_str(),
                param_name );
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetAcceleratorInfoINTEL(
                accelerator,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_accelerator
CL_API_ENTRY cl_int CL_API_CALL clRetainAcceleratorINTEL(
    cl_accelerator_intel accelerator )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(accelerator);
        if( dispatchX.clRetainAcceleratorINTEL )
        {
            cl_uint ref_count = 0;
            if( pIntercept->callLogging() )
            {
                ref_count = 0;
                dispatchX.clGetAcceleratorInfoINTEL(
                    accelerator,
                    CL_ACCELERATOR_REFERENCE_COUNT_INTEL,
                    sizeof( ref_count ),
                    &ref_count,
                    NULL );
            }
            CALL_LOGGING_ENTER( "[ ref count = %d ] accelerator = %p",
                ref_count,
                accelerator );
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clRetainAcceleratorINTEL(
                accelerator );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            if( pIntercept->callLogging() )
            {
                ref_count = 0;
                dispatchX.clGetAcceleratorInfoINTEL(
                    accelerator,
                    CL_ACCELERATOR_REFERENCE_COUNT_INTEL,
                    sizeof( ref_count ),
                    &ref_count,
                    NULL );
            }
            CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_accelerator
CL_API_ENTRY cl_int CL_API_CALL clReleaseAcceleratorINTEL(
    cl_accelerator_intel accelerator )
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(accelerator);
        if( dispatchX.clReleaseAcceleratorINTEL )
        {
            cl_uint ref_count = 0;
            if( pIntercept->callLogging() )
            {
                ref_count = 0;
                dispatchX.clGetAcceleratorInfoINTEL(
                    accelerator,
                    CL_ACCELERATOR_REFERENCE_COUNT_INTEL,
                    sizeof( ref_count ),
                    &ref_count,
                    NULL );
            }
            CALL_LOGGING_ENTER( "[ ref count = %d ] accelerator = %p",
                ref_count,
                accelerator );
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clReleaseAcceleratorINTEL(
                accelerator );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            if( pIntercept->callLogging() && ref_count != 0 )
            {
                // This isn't strictly correct, but it's pretty close, and it
                // avoids crashes in some cases for bad implementations.
                --ref_count;
            }
            CALL_LOGGING_EXIT( retVal, "[ ref count = %d ]", ref_count );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_va_api_media_sharing
CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
    cl_platform_id platform,
    cl_va_api_device_source_intel media_adapter_type,
    void *media_adapter,
    cl_va_api_device_set_intel media_adapter_set,
    cl_uint num_entries,
    cl_device_id *devices,
    cl_uint *num_devices)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(platform);
        if( dispatchX.clGetDeviceIDsFromVA_APIMediaAdapterINTEL )
        {
            CALL_LOGGING_ENTER();
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetDeviceIDsFromVA_APIMediaAdapterINTEL(
                platform,
                media_adapter_type,
                media_adapter,
                media_adapter_set,
                num_entries,
                devices,
                num_devices);

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_va_api_media_sharing
CL_API_ENTRY cl_mem CL_API_CALL clCreateFromVA_APIMediaSurfaceINTEL(
    cl_context context,
    cl_mem_flags flags,
    VASurfaceID *surface,
    cl_uint plane,
    cl_int *errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clCreateFromVA_APIMediaSurfaceINTEL )
        {
            CALL_LOGGING_ENTER(
                "context = %p, "
                "flags = %s (%llX)",
                context,
                pIntercept->enumName().name_mem_flags( flags ).c_str(),
                flags );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            cl_mem  retVal = dispatchX.clCreateFromVA_APIMediaSurfaceINTEL(
                context,
                flags,
                surface,
                plane,
                errcode_ret);

            CPU_PERFORMANCE_TIMING_END();
            ADD_IMAGE( retVal );
            CHECK_ERROR( errcode_ret[0] );
            ADD_OBJECT_ALLOCATION( retVal );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_va_api_media_sharing
CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireVA_APIMediaSurfacesINTEL(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem *mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueAcquireVA_APIMediaSurfacesINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueAcquireVA_APIMediaSurfacesINTEL(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_va_api_media_sharing
CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseVA_APIMediaSurfacesINTEL(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem *mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(command_queue);
        if( dispatchX.clEnqueueReleaseVA_APIMediaSurfacesINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( command_queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER();
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueReleaseVA_APIMediaSurfacesINTEL(
                    command_queue,
                    num_objects,
                    mem_objects,
                    num_events_in_wait_list,
                    event_wait_list,
                    event);

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( command_queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( command_queue );
            CHECK_AUBCAPTURE_STOP( command_queue );

            DEVICE_PERFORMANCE_TIMING_CHECK();

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY void* CL_API_CALL clHostMemAllocINTEL(
    cl_context context,
    const cl_mem_properties_intel* properties,
    size_t size,
    cl_uint alignment,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clHostMemAllocINTEL )
        {
            // TODO: Make properties string.
            CALL_LOGGING_ENTER( "context = %p, properties = %p, size = %d, alignment = %d",
                context,
                properties,
                size,
                alignment );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            void*   retVal = dispatchX.clHostMemAllocINTEL(
                context,
                properties,
                size,
                alignment,
                errcode_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( errcode_ret[0] );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY void* CL_API_CALL clDeviceMemAllocINTEL(
    cl_context context,
    cl_device_id device,
    const cl_mem_properties_intel* properties,
    size_t size,
    cl_uint alignment,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clDeviceMemAllocINTEL )
        {
            std::string deviceInfo;
            if( pIntercept->config().CallLogging )
            {
                pIntercept->getDeviceInfoString(
                    1,
                    &device,
                    deviceInfo );
            }
            // TODO: Make properties string.
            CALL_LOGGING_ENTER( "context = %p, device = [ %s ], properties = %p, size = %d, alignment = %d",
                context,
                deviceInfo.c_str(),
                properties,
                size,
                alignment );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            void*   retVal = dispatchX.clDeviceMemAllocINTEL(
                context,
                device,
                properties,
                size,
                alignment,
                errcode_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( errcode_ret[0] );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY void* CL_API_CALL clSharedMemAllocINTEL(
    cl_context context,
    cl_device_id device,
    const cl_mem_properties_intel* properties,
    size_t size,
    cl_uint alignment,
    cl_int* errcode_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clSharedMemAllocINTEL )
        {
            std::string deviceInfo;
            if( pIntercept->config().CallLogging )
            {
                pIntercept->getDeviceInfoString(
                    1,
                    &device,
                    deviceInfo );
            }
            // TODO: Make properties string.
            CALL_LOGGING_ENTER( "context = %p, device = [ %s ], properties = %p, size = %d, alignment = %d",
                context,
                deviceInfo.c_str(),
                properties,
                size,
                alignment );
            CHECK_ERROR_INIT( errcode_ret );
            CPU_PERFORMANCE_TIMING_START();

            void*   retVal = dispatchX.clSharedMemAllocINTEL(
                context,
                device,
                properties,
                size,
                alignment,
                errcode_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( errcode_ret[0] );
            CALL_LOGGING_EXIT( errcode_ret[0], "returned %p", retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_SET_ERROR_RETURN_NULL(errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL clMemFreeINTEL(
    cl_context context,
    void* ptr)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clMemFreeINTEL )
        {
            CALL_LOGGING_ENTER( "context = %p, ptr = %p",
                context,
                ptr );
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clMemFreeINTEL(
                context,
                ptr );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL
clMemBlockingFreeINTEL(
    cl_context context,
    void* ptr)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clMemBlockingFreeINTEL )
        {
            CALL_LOGGING_ENTER( "context = %p, ptr = %p",
                context,
                ptr );
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clMemBlockingFreeINTEL(
                context,
                ptr );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL clGetMemAllocInfoINTEL(
    cl_context context,
    const void* ptr,
    cl_mem_info_intel param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(context);
        if( dispatchX.clGetMemAllocInfoINTEL )
        {
            CALL_LOGGING_ENTER( "context = %p, ptr = %p, param_name = %s (%08X)",
                context,
                ptr,
                pIntercept->enumName().name( param_name ).c_str(),
                param_name );
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clGetMemAllocInfoINTEL(
                context,
                ptr,
                param_name,
                param_value_size,
                param_value,
                param_value_size_ret );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL clSetKernelArgMemPointerINTEL(
    cl_kernel kernel,
    cl_uint arg_index,
    const void* arg_value)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(kernel);
        if( dispatchX.clSetKernelArgMemPointerINTEL )
        {
            CALL_LOGGING_ENTER_KERNEL(
                kernel,
                "kernel = %p, index = %d, value = %p",
                kernel,
                arg_index,
                arg_value );
            CHECK_KERNEL_ARG_USM_POINTER( kernel, arg_value );
            CPU_PERFORMANCE_TIMING_START();

            cl_int  retVal = dispatchX.clSetKernelArgMemPointerINTEL(
                kernel,
                arg_index,
                arg_value );

            CPU_PERFORMANCE_TIMING_END();
            CHECK_ERROR( retVal );
            CALL_LOGGING_EXIT( retVal );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL clEnqueueMemsetINTEL(   // Deprecated
    cl_command_queue queue,
    void* dst_ptr,
    cl_int value,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(queue);
        if( dispatchX.clEnqueueMemsetINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER( "queue = %p, dst_ptr = %p, value = %d, size = %u",
                    queue,
                    dst_ptr,
                    value,
                    (cl_uint)size );
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueMemsetINTEL(
                    queue,
                    dst_ptr,
                    value,
                    size,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( queue );
            CHECK_AUBCAPTURE_STOP( queue  );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL clEnqueueMemFillINTEL(
    cl_command_queue queue,
    void* dst_ptr,
    const void* pattern,
    size_t pattern_size,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(queue);
        if( dispatchX.clEnqueueMemFillINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER( "queue = %p, dst_ptr = %p, pattern_size = %u, size = %u",
                    queue,
                    dst_ptr,
                    (cl_uint)pattern_size,
                    (cl_uint)size );
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueMemFillINTEL(
                    queue,
                    dst_ptr,
                    pattern,
                    pattern_size,
                    size,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( queue );
            CHECK_AUBCAPTURE_STOP( queue  );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL clEnqueueMemcpyINTEL(
    cl_command_queue queue,
    cl_bool blocking,
    void* dst_ptr,
    const void* src_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(queue);
        if( dispatchX.clEnqueueMemcpyINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER( "queue = %p, %s, dst_ptr = %p, src_ptr = %p, size = %u",
                    queue,
                    blocking ? "blocking" : "non-blocking",
                    dst_ptr,
                    src_ptr,
                    (cl_uint)size );
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueMemcpyINTEL(
                    queue,
                    blocking,
                    dst_ptr,
                    src_ptr,
                    size,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( queue );
            CHECK_AUBCAPTURE_STOP( queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL clEnqueueMigrateMemINTEL(
    cl_command_queue queue,
    const void* ptr,
    size_t size,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(queue);
        if( dispatchX.clEnqueueMigrateMemINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER( "queue = %p, ptr = %p, size = %u, flags = %s (%llX)",
                    queue,
                    ptr,
                    (cl_uint)size,
                    pIntercept->enumName().name_mem_migration_flags( flags ).c_str(),
                    flags );
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueMigrateMemINTEL(
                    queue,
                    ptr,
                    size,
                    flags,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( queue );
            CHECK_AUBCAPTURE_STOP( queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

///////////////////////////////////////////////////////////////////////////////
//
// cl_intel_unified_shared_memory
CL_API_ENTRY cl_int CL_API_CALL clEnqueueMemAdviseINTEL(
    cl_command_queue queue,
    const void* ptr,
    size_t size,
    cl_mem_advice_intel advice,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    CLIntercept*    pIntercept = GetIntercept();

    if( pIntercept )
    {
        auto dispatchX = pIntercept->dispatchX(queue);
        if( dispatchX.clEnqueueMemAdviseINTEL )
        {
            cl_int  retVal = CL_SUCCESS;

            CHECK_AUBCAPTURE_START( queue );

            if( pIntercept->nullEnqueue() == false )
            {
                CALL_LOGGING_ENTER( "queue = %p, ptr = %p, size = %u, advice = %s (%llX)",
                    queue,
                    ptr,
                    (cl_uint)size,
                    pIntercept->enumName().name(advice).c_str(),
                    advice );
                CHECK_EVENT_LIST( num_events_in_wait_list, event_wait_list, event );
                DEVICE_PERFORMANCE_TIMING_START( event );
                CPU_PERFORMANCE_TIMING_START();

                retVal = dispatchX.clEnqueueMemAdviseINTEL(
                    queue,
                    ptr,
                    size,
                    advice,
                    num_events_in_wait_list,
                    event_wait_list,
                    event );

                CPU_PERFORMANCE_TIMING_END();
                DEVICE_PERFORMANCE_TIMING_END( queue, event );
                CHECK_ERROR( retVal );
                ADD_OBJECT_ALLOCATION( event ? event[0] : NULL );
                CALL_LOGGING_EXIT_EVENT( retVal, event );
            }

            FINISH_OR_FLUSH_AFTER_ENQUEUE( queue );
            CHECK_AUBCAPTURE_STOP( queue );

            return retVal;
        }
    }

    NULL_FUNCTION_POINTER_RETURN_ERROR();
}

#if defined(__APPLE__)
#include "OS/OS_mac_interpose.h"
#endif
