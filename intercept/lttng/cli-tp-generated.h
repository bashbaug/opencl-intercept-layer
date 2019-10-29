/*
// Copyright (c) 2018-2019 Intel Corporation
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

// This file is automatically genererated from cli-tp.h.mako!
// Please do not edit it manually!


TRACEPOINT_EVENT(
    CLIntercept,
    clGetPlatformIDs,
    TP_ARGS(
        cl_uint, num_entries,
        cl_platform_id*, platforms,
        cl_uint*, num_platforms
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetPlatformInfo,
    TP_ARGS(
        cl_platform_id, platform,
        cl_platform_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetDeviceIDs,
    TP_ARGS(
        cl_platform_id, platform,
        cl_device_type, device_type,
        cl_uint, num_entries,
        cl_device_id*, devices,
        cl_uint*, num_devices
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetDeviceInfo,
    TP_ARGS(
        cl_device_id, device,
        cl_device_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateContext,
    TP_ARGS(
        const cl_context_properties*, properties,
        cl_uint, num_devices,
        const cl_device_id*, devices,
        void*, pfn_notify,   //void (CL_CALLBACK*)(const char*, const void*, size_t, void*)
        void*, user_data,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateContextFromType,
    TP_ARGS(
        const cl_context_properties*, properties,
        cl_device_type, device_type,
        void*, pfn_notify,   //void (CL_CALLBACK*)(const char*, const void*, size_t, void*)
        void*, user_data,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clRetainContext,
    TP_ARGS(
        cl_context, context
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clReleaseContext,
    TP_ARGS(
        cl_context, context
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetContextInfo,
    TP_ARGS(
        cl_context, context,
        cl_context_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clRetainCommandQueue,
    TP_ARGS(
        cl_command_queue, command_queue
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clReleaseCommandQueue,
    TP_ARGS(
        cl_command_queue, command_queue
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetCommandQueueInfo,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_command_queue_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateBuffer,
    TP_ARGS(
        cl_context, context,
        cl_mem_flags, flags,
        size_t, size,
        void*, host_ptr,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clRetainMemObject,
    TP_ARGS(
        cl_mem, memobj
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clReleaseMemObject,
    TP_ARGS(
        cl_mem, memobj
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetSupportedImageFormats,
    TP_ARGS(
        cl_context, context,
        cl_mem_flags, flags,
        cl_mem_object_type, image_type,
        cl_uint, num_entries,
        cl_image_format*, image_formats,
        cl_uint*, num_image_formats
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetMemObjectInfo,
    TP_ARGS(
        cl_mem, memobj,
        cl_mem_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetImageInfo,
    TP_ARGS(
        cl_mem, image,
        cl_image_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clRetainSampler,
    TP_ARGS(
        cl_sampler, sampler
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clReleaseSampler,
    TP_ARGS(
        cl_sampler, sampler
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetSamplerInfo,
    TP_ARGS(
        cl_sampler, sampler,
        cl_sampler_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateProgramWithSource,
    TP_ARGS(
        cl_context, context,
        cl_uint, count,
        const char**, strings,
        const size_t*, lengths,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateProgramWithBinary,
    TP_ARGS(
        cl_context, context,
        cl_uint, num_devices,
        const cl_device_id*, device_list,
        const size_t*, lengths,
        const unsigned char**, binaries,
        cl_int*, binary_status,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clRetainProgram,
    TP_ARGS(
        cl_program, program
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clReleaseProgram,
    TP_ARGS(
        cl_program, program
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clBuildProgram,
    TP_ARGS(
        cl_program, program,
        cl_uint, num_devices,
        const cl_device_id*, device_list,
        const char*, options,
        void*, pfn_notify,   //void (CL_CALLBACK*)(cl_program program, void* user_data)
        void*, user_data
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetProgramInfo,
    TP_ARGS(
        cl_program, program,
        cl_program_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetProgramBuildInfo,
    TP_ARGS(
        cl_program, program,
        cl_device_id, device,
        cl_program_build_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateKernel,
    TP_ARGS(
        cl_program, program,
        const char*, kernel_name,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateKernelsInProgram,
    TP_ARGS(
        cl_program, program,
        cl_uint, num_kernels,
        cl_kernel*, kernels,
        cl_uint*, num_kernels_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clRetainKernel,
    TP_ARGS(
        cl_kernel, kernel
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clReleaseKernel,
    TP_ARGS(
        cl_kernel, kernel
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetKernelArg,
    TP_ARGS(
        cl_kernel, kernel,
        cl_uint, arg_index,
        size_t, arg_size,
        const void*, arg_value
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetKernelInfo,
    TP_ARGS(
        cl_kernel, kernel,
        cl_kernel_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetKernelWorkGroupInfo,
    TP_ARGS(
        cl_kernel, kernel,
        cl_device_id, device,
        cl_kernel_work_group_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clWaitForEvents,
    TP_ARGS(
        cl_uint, num_events,
        const cl_event*, event_list
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetEventInfo,
    TP_ARGS(
        cl_event, event,
        cl_event_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clRetainEvent,
    TP_ARGS(
        cl_event, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clReleaseEvent,
    TP_ARGS(
        cl_event, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetEventProfilingInfo,
    TP_ARGS(
        cl_event, event,
        cl_profiling_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clFlush,
    TP_ARGS(
        cl_command_queue, command_queue
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clFinish,
    TP_ARGS(
        cl_command_queue, command_queue
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueReadBuffer,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, buffer,
        cl_bool, blocking_read,
        size_t, offset,
        size_t, size,
        void*, ptr,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueWriteBuffer,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, buffer,
        cl_bool, blocking_write,
        size_t, offset,
        size_t, size,
        const void*, ptr,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueCopyBuffer,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, src_buffer,
        cl_mem, dst_buffer,
        size_t, src_offset,
        size_t, dst_offset,
        size_t, size,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

// clEnqueueReadImage has too many parameters and cannot be automatically generated.

// clEnqueueWriteImage has too many parameters and cannot be automatically generated.

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueCopyImage,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, src_image,
        cl_mem, dst_image,
        const size_t*, src_origin,
        const size_t*, dst_origin,
        const size_t*, region,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueCopyImageToBuffer,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, src_image,
        cl_mem, dst_buffer,
        const size_t*, src_origin,
        const size_t*, region,
        size_t, dst_offset,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueCopyBufferToImage,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, src_buffer,
        cl_mem, dst_image,
        size_t, src_offset,
        const size_t*, dst_origin,
        const size_t*, region,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

// clEnqueueMapBuffer has too many parameters and cannot be automatically generated.

// clEnqueueMapImage has too many parameters and cannot be automatically generated.

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueUnmapMemObject,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, memobj,
        void*, mapped_ptr,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueNDRangeKernel,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_kernel, kernel,
        cl_uint, work_dim,
        const size_t*, global_work_offset,
        const size_t*, global_work_size,
        const size_t*, local_work_size,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

// clEnqueueNativeKernel has too many parameters and cannot be automatically generated.

TRACEPOINT_EVENT(
    CLIntercept,
    clSetCommandQueueProperty,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_command_queue_properties, properties,
        cl_bool, enable,
        cl_command_queue_properties*, old_properties
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateImage2D,
    TP_ARGS(
        cl_context, context,
        cl_mem_flags, flags,
        const cl_image_format*, image_format,
        size_t, image_width,
        size_t, image_height,
        size_t, image_row_pitch,
        void*, host_ptr,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

// clCreateImage3D has too many parameters and cannot be automatically generated.

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueMarker,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueWaitForEvents,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_uint, num_events,
        const cl_event*, event_list
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueBarrier,
    TP_ARGS(
        cl_command_queue, command_queue
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clUnloadCompiler,
    TP_ARGS(
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetExtensionFunctionAddress,
    TP_ARGS(
        const char*, func_name
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateCommandQueue,
    TP_ARGS(
        cl_context, context,
        cl_device_id, device,
        cl_command_queue_properties, properties,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateSampler,
    TP_ARGS(
        cl_context, context,
        cl_bool, normalized_coords,
        cl_addressing_mode, addressing_mode,
        cl_filter_mode, filter_mode,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueTask,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_kernel, kernel,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateSubBuffer,
    TP_ARGS(
        cl_mem, buffer,
        cl_mem_flags, flags,
        cl_buffer_create_type, buffer_create_type,
        const void*, buffer_create_info,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetMemObjectDestructorCallback,
    TP_ARGS(
        cl_mem, memobj,
        void*, pfn_notify,   //void (CL_CALLBACK*)(cl_mem memobj, void* user_data)
        void*, user_data
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateUserEvent,
    TP_ARGS(
        cl_context, context,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetUserEventStatus,
    TP_ARGS(
        cl_event, event,
        cl_int, execution_status
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetEventCallback,
    TP_ARGS(
        cl_event, event,
        cl_int, command_exec_callback_type,
        void*, pfn_notify,   //void (CL_CALLBACK*)(cl_event event, cl_int type, void *user_data)
        void*, user_data
    ),
    TP_FIELDS(
    )
)

// clEnqueueReadBufferRect has too many parameters and cannot be automatically generated.

// clEnqueueWriteBufferRect has too many parameters and cannot be automatically generated.

// clEnqueueCopyBufferRect has too many parameters and cannot be automatically generated.

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateSubDevices,
    TP_ARGS(
        cl_device_id, in_device,
        const cl_device_partition_property*, properties,
        cl_uint, num_devices,
        cl_device_id*, out_devices,
        cl_uint*, num_devices_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clRetainDevice,
    TP_ARGS(
        cl_device_id, device
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clReleaseDevice,
    TP_ARGS(
        cl_device_id, device
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateImage,
    TP_ARGS(
        cl_context, context,
        cl_mem_flags, flags,
        const cl_image_format*, image_format,
        const cl_image_desc*, image_desc,
        void*, host_ptr,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateProgramWithBuiltInKernels,
    TP_ARGS(
        cl_context, context,
        cl_uint, num_devices,
        const cl_device_id*, device_list,
        const char*, kernel_names,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCompileProgram,
    TP_ARGS(
        cl_program, program,
        cl_uint, num_devices,
        const cl_device_id*, device_list,
        const char*, options,
        cl_uint, num_input_headers,
        const cl_program*, input_headers,
        const char**, header_include_names,
        void*, pfn_notify,   //void (CL_CALLBACK*)(cl_program program, void* user_data)
        void*, user_data
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clLinkProgram,
    TP_ARGS(
        cl_context, context,
        cl_uint, num_devices,
        const cl_device_id*, device_list,
        const char*, options,
        cl_uint, num_input_programs,
        const cl_program*, input_programs,
        void*, pfn_notify,   //void (CL_CALLBACK*)(cl_program program, void* user_data)
        void*, user_data,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clUnloadPlatformCompiler,
    TP_ARGS(
        cl_platform_id, platform
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetKernelArgInfo,
    TP_ARGS(
        cl_kernel, kernel,
        cl_uint, arg_indx,
        cl_kernel_arg_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueFillBuffer,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, buffer,
        const void*, pattern,
        size_t, pattern_size,
        size_t, offset,
        size_t, size,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueFillImage,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_mem, image,
        const void*, fill_color,
        const size_t*, origin,
        const size_t*, region,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueMigrateMemObjects,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_uint, num_mem_objects,
        const cl_mem*, mem_objects,
        cl_mem_migration_flags, flags,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueMarkerWithWaitList,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueBarrierWithWaitList,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetExtensionFunctionAddressForPlatform,
    TP_ARGS(
        cl_platform_id, platform,
        const char*, func_name
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateCommandQueueWithProperties,
    TP_ARGS(
        cl_context, context,
        cl_device_id, device,
        const cl_queue_properties*, properties,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreatePipe,
    TP_ARGS(
        cl_context, context,
        cl_mem_flags, flags,
        cl_uint, pipe_packet_size,
        cl_uint, pipe_max_packets,
        const cl_pipe_properties*, properties,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetPipeInfo,
    TP_ARGS(
        cl_mem, pipe,
        cl_pipe_info, param_name,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSVMAlloc,
    TP_ARGS(
        cl_context, context,
        cl_svm_mem_flags, flags,
        size_t, size,
        cl_uint, alignment
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSVMFree,
    TP_ARGS(
        cl_context, context,
        void*, svm_pointer
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateSamplerWithProperties,
    TP_ARGS(
        cl_context, context,
        const cl_sampler_properties*, sampler_properties,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetKernelArgSVMPointer,
    TP_ARGS(
        cl_kernel, kernel,
        cl_uint, arg_index,
        const void*, arg_value
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetKernelExecInfo,
    TP_ARGS(
        cl_kernel, kernel,
        cl_kernel_exec_info, param_name,
        size_t, param_value_size,
        const void*, param_value
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueSVMFree,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_uint, num_svm_pointers,
        void**, svm_pointers,
        void*, pfn_free_func,   //void (CL_CALLBACK*)(cl_command_queue queue, cl_uint num_svm_pointers, void* svm_pointers[], void* user_data)
        void*, user_data,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueSVMMemcpy,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_bool, blocking_copy,
        void*, dst_ptr,
        const void*, src_ptr,
        size_t, size,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueSVMMemFill,
    TP_ARGS(
        cl_command_queue, command_queue,
        void*, svm_ptr,
        const void*, pattern,
        size_t, pattern_size,
        size_t, size,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueSVMMap,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_bool, blocking_map,
        cl_map_flags, flags,
        void*, svm_ptr,
        size_t, size,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueSVMUnmap,
    TP_ARGS(
        cl_command_queue, command_queue,
        void*, svm_ptr,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetDefaultDeviceCommandQueue,
    TP_ARGS(
        cl_context, context,
        cl_device_id, device,
        cl_command_queue, command_queue
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetDeviceAndHostTimer,
    TP_ARGS(
        cl_device_id, device,
        cl_ulong*, device_timestamp,
        cl_ulong*, host_timestamp
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetHostTimer,
    TP_ARGS(
        cl_device_id, device,
        cl_ulong*, host_timestamp
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCreateProgramWithIL,
    TP_ARGS(
        cl_context, context,
        const void*, il,
        size_t, length,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clCloneKernel,
    TP_ARGS(
        cl_kernel, source_kernel,
        cl_int*, errcode_ret
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clGetKernelSubGroupInfo,
    TP_ARGS(
        cl_kernel, kernel,
        cl_device_id, device,
        cl_kernel_sub_group_info, param_name,
        size_t, input_value_size,
        const void*, input_value,
        size_t, param_value_size,
        void*, param_value,
        size_t*, param_value_size_ret
    ),
    TP_FIELDS(
        ctf_integer_hex(int, param_name, param_name)
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clEnqueueSVMMigrateMem,
    TP_ARGS(
        cl_command_queue, command_queue,
        cl_uint, num_svm_pointers,
        const void**, svm_pointers,
        const size_t*, sizes,
        cl_mem_migration_flags, flags,
        cl_uint, num_events_in_wait_list,
        const cl_event*, event_wait_list,
        cl_event*, event
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetProgramReleaseCallback,
    TP_ARGS(
        cl_program, program,
        void*, pfn_notify,   //void (CL_CALLBACK*)(cl_program program, void* user_data)
        void*, user_data
    ),
    TP_FIELDS(
    )
)

TRACEPOINT_EVENT(
    CLIntercept,
    clSetProgramSpecializationConstant,
    TP_ARGS(
        cl_program, program,
        cl_uint, spec_id,
        size_t, spec_size,
        const void*, spec_value
    ),
    TP_FIELDS(
    )
)
