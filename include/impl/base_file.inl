/*
 * Copyright 2018 Justas Masiulis
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "../io/base_file.hpp"

#define NTW_BUILDER_OPTION(builder, function_name, member, value, op) \
    NTW_INLINE constexpr builder& builder::function_name()            \
    {                                                                 \
        _data.member op value;                                        \
        return *this;                                                 \
    }

#define NTW_FILE_OPTION(name, member, value, op) \
    template<class Base>                         \
    NTW_BUILDER_OPTION(file_options_builder<Base>, name, member, value, op)

#define NTW_FILE_ATTRIBUTE_OPTION(name, value, op) \
    NTW_BUILDER_OPTION(file_attributes_builder, name, attributes, value, op)

#define NTW_PIPE_OPTION(name, member, value, op) \
    NTW_BUILDER_OPTION(pipe_options_builder, name, member, value, op)

namespace ntw::io::detail {

    NTW_FILE_OPTION(reset_share_access, share_access, 0, =)
    NTW_FILE_OPTION(share_read, share_access, FILE_SHARE_READ, |=)
    NTW_FILE_OPTION(share_write, share_access, FILE_SHARE_WRITE, |=)
    NTW_FILE_OPTION(share_delete, share_access, FILE_SHARE_DELETE, |=)
    NTW_FILE_OPTION(share_all, share_access, 0b111, =)

    NTW_FILE_OPTION(reset_create_options, options, 0, =)
    NTW_FILE_OPTION(write_trough, options, FILE_WRITE_THROUGH, |=)
    NTW_FILE_OPTION(sequential_access, options, FILE_SEQUENTIAL_ONLY, |=)
    NTW_FILE_OPTION(random_access, options, FILE_RANDOM_ACCESS, |=)
    NTW_FILE_OPTION(create_tree_connection, options, FILE_CREATE_TREE_CONNECTION, |=)
    NTW_FILE_OPTION(no_ea_knownledge, options, FILE_NO_EA_KNOWLEDGE, |=)
    NTW_FILE_OPTION(open_reparse_point, options, FILE_OPEN_REPARSE_POINT, |=)
    NTW_FILE_OPTION(delete_on_close, options, FILE_DELETE_ON_CLOSE, |=)
    NTW_FILE_OPTION(open_by_file_id, options, FILE_OPEN_BY_FILE_ID, |=)
    NTW_FILE_OPTION(open_for_backup, options, FILE_OPEN_FOR_BACKUP_INTENT, |=)
    NTW_FILE_OPTION(reserve_opfilter, options, FILE_RESERVE_OPFILTER, |=)
    NTW_FILE_OPTION(requires_oplock, options, FILE_OPEN_REQUIRING_OPLOCK, |=)
    NTW_FILE_OPTION(complete_if_oplocked, options, FILE_COMPLETE_IF_OPLOCKED, |=)

    NTW_FILE_OPTION(reset_access, access, 0, =);

    NTW_FILE_OPTION(full_access, access, GENERIC_ALL, =);

    NTW_FILE_OPTION(deleteable, access, DELETE, |=)
    NTW_FILE_OPTION(synchronizable, access, SYNCHRONIZE, |=)
    NTW_FILE_OPTION(executeable, access, FILE_EXECUTE, |=)
    NTW_FILE_OPTION(traversible, access, FILE_TRAVERSE, |=)
    NTW_FILE_OPTION(listable_directory, access, FILE_LIST_DIRECTORY, |=)

    NTW_FILE_OPTION(generic_readable, access, FILE_GENERIC_READ, |=)
    NTW_FILE_OPTION(generic_writeable, access, FILE_GENERIC_WRITE, |=)
    NTW_FILE_OPTION(generic_executeable, access, FILE_GENERIC_EXECUTE, |=)

    NTW_FILE_OPTION(readable_data, access, FILE_READ_DATA, |=)
    NTW_FILE_OPTION(readable_attributes, access, FILE_READ_ATTRIBUTES, |=)
    NTW_FILE_OPTION(readable_extended_attributes, access, FILE_READ_EA, |=)
    NTW_FILE_OPTION(readable_access_control, access, READ_CONTROL, |=)

    NTW_FILE_OPTION(writeable_data, access, FILE_WRITE_DATA, |=)
    NTW_FILE_OPTION(writeable_attributes, access, FILE_WRITE_ATTRIBUTES |=)
    NTW_FILE_OPTION(writeable_extended_attributes, access, FILE_WRITE_EA, |=)
    NTW_FILE_OPTION(writeable_access_control, access, WRITE_DAC, |=)
    NTW_FILE_OPTION(writeable_ownership, access, WRITE_OWNER, |=)
    NTW_FILE_OPTION(appendable_data, access, FILE_APPEND_DATA, |=)

    NTW_FILE_ATTRIBUTE_OPTION(reset_attributes, 0, =);
    NTW_FILE_ATTRIBUTE_OPTION(archive, FILE_ATTRIBUTE_ARCHIVE, |=)
    NTW_FILE_ATTRIBUTE_OPTION(encrypted, FILE_ATTRIBUTE_ENCRYPTED, |=)
    NTW_FILE_ATTRIBUTE_OPTION(hidden, FILE_ATTRIBUTE_HIDDEN, |=)
    NTW_FILE_ATTRIBUTE_OPTION(normal, FILE_ATTRIBUTE_NORMAL, |=)
    NTW_FILE_ATTRIBUTE_OPTION(offline, FILE_ATTRIBUTE_OFFLINE, |=)
    NTW_FILE_ATTRIBUTE_OPTION(readonly, FILE_ATTRIBUTE_READONLY, |=)
    NTW_FILE_ATTRIBUTE_OPTION(system, FILE_ATTRIBUTE_SYSTEM, |=)
    NTW_FILE_ATTRIBUTE_OPTION(temporary, FILE_ATTRIBUTE_TEMPORARY, |=)

    NTW_PIPE_OPTION(reset_type, type, 0, =)
    NTW_PIPE_OPTION(byte_stream, type, FILE_PIPE_MESSAGE_MODE, &= ~)
    NTW_PIPE_OPTION(message_stream, type, FILE_PIPE_MESSAGE_TYPE, |=)
    NTW_PIPE_OPTION(accept_remote_clients, type, FILE_PIPE_ACCEPT_REMOTE_CLIENTS, |=)
    NTW_PIPE_OPTION(reject_remote_clients, type, FILE_PIPE_REJECT_REMOTE_CLIENTS, |=)

    template<class Base>
    NTW_INLINE constexpr file_options_builder<Base>
    file_options_builder<Base>::copy() const
    {
        return *this;
    }


    NTW_INLINE constexpr pipe_options_builder& pipe_options_builder::qouta(
        ulong_t inbound, ulong_t outbound)
    {
        _data.inbound_qouta  = inbound;
        _data.outbound_qouta = outbound;
        return *this;
    }

    NTW_INLINE constexpr pipe_options_builder& pipe_options_builder::inbound_qouta(
        ulong_t qouta)
    {
        _data.inbound_qouta = qouta;
        return *this;
    }

    NTW_INLINE constexpr pipe_options_builder& pipe_options_builder::outbound_qouta(
        ulong_t qouta)
    {
        _data.outbound_qouta = qouta;
        return *this;
    }


    NTW_INLINE constexpr pipe_options_builder& pipe_options_builder::instances_limit(
        ulong_t limit)
    {
        _data.instances_limit = limit;
        return *this;
    }

    // default = 5 seconds
    NTW_INLINE constexpr pipe_options_builder& pipe_options_builder::timeout(
        std::int64_t nanoseconds)
    {
        // the timeout is a negative value
        if(nanoseconds > 0)
            nanoseconds = -nanoseconds;
        _data.timeout = nanoseconds;
        return *this;
    }

    NTW_INLINE constexpr ulong_t file_attributes_builder::attributes() const
    {
        return _data.attributes;
    }

    NTW_INLINE constexpr const pipe_options_data& pipe_options_builder::pipe_data() const
    {
        return _data;
    }

    template<class Base>
    NTW_INLINE constexpr const file_options_data& file_options_builder<Base>::data() const
    {
        return _data;
    }

    template<class Traits>
    NT_FN base_file<Traits>::_open(UNICODE_STRING      path,
                                   const file_options& options,
                                   ulong_t             disposition) noexcept
    {
        auto  attributes  = make_attributes(&path, OBJ_CASE_INSENSITIVE);
        void* temp_handle = nullptr;

        const auto status = Traits::open(temp_handle, attributes, options, disposition);

        if(NT_SUCCESS(status))
            _handle.reset(temp_handle);

        return status;
    }


    template<class Traits>
    template<class StringRef>
    NT_FN base_file<Traits>::open(const StringRef&    path,
                                  const file_options& options) noexcept
    {
        return _open(make_ustr(path), options, FILE_OPEN);
    }

    template<class Traits>
    template<class StringRef>
    NT_FN base_file<Traits>::create(const StringRef&    path,
                                    const file_options& options) noexcept
    {
        return _open(make_ustr(path), options, FILE_CREATE);
    }

    template<class Traits>
    template<class StringRef>
    NT_FN base_file<Traits>::supersede(const StringRef&    path,
                                       const file_options& options) noexcept
    {
        return _open(make_ustr(path), options, FILE_SUPERSEDE);
    }

    template<class Traits>
    template<class StringRef>
    NT_FN base_file<Traits>::overwrite(const StringRef&    path,
                                       const file_options& options) noexcept
    {
        return _open(make_ustr(path), options, FILE_OVERWRITE);
    }

    template<class Traits>
    template<class StringRef>
    NT_FN base_file<Traits>::open_or_create(const StringRef&    path,
                                            const file_options& options) noexcept
    {
        return _open(make_ustr(path), options, FILE_OPEN_IF);
    }

    template<class Traits>
    template<class StringRef>
    NT_FN base_file<Traits>::overwrite_or_create(const StringRef&    path,
                                                 const file_options& options) noexcept
    {
        return _open(make_ustr(path), options, FILE_OVERWRITE_IF);
    }


    template<class Traits>
    NT_FN base_file<Traits>::size(std::uint64_t& size_out) const noexcept
    {
        IO_STATUS_BLOCK           status_block;
        FILE_STANDARD_INFORMATION info;
        const auto                status = LI_NT(NtQueryInformationFile)(_handle.get(),
                                                          &status_block,
                                                          &info,
                                                          unsigned{ sizeof(info) },
                                                          FileStandardInformation);
        if(NT_SUCCESS(status))
            size_out = static_cast<std::uint64_t>(info.EndOfFile.QuadPart);

        return status;
    }

    template<class Traits>
    template<class StringRef /* wstring_view or UNICODE_STRING */>
    NT_FN base_file<Traits>::destroy(const StringRef& path, bool case_sensitive) noexcept
    {
        auto upath = make_ustr(path);
        auto attributes =
            make_attributes(&upath, case_sensitive ? 0 : OBJ_CASE_INSENSITIVE);
        return LI_NT(NtDeleteFile)(&attributes);
    }

    template<class Traits>
    template<class Buffer, class>
    NT_FN base_file<Traits>::info(FILE_INFORMATION_CLASS info_class,
                                  Buffer&                buffer,
                                  ulong_t                size,
                                  ulong_t*               returned) const noexcept
    {
        IO_STATUS_BLOCK iosb;
        const auto      status = LI_NT(NtQueryInformationFile)(
            handle().get(), &iosb, ::std::addressof(buffer), size, info_class);
        if(returned && NT_SUCCESS(status))
            *returned = iosb.Information;

        return status;
    }

    template<class Traits>
    template<class Callback, class... Args, class>
    NT_FN base_file<Traits>::info(FILE_INFORMATION_CLASS info_class,
                                  Callback               cb,
                                  Args&&... args) const
    {
        NTW_IMPLEMENT_QUERY_CALLBACK
    }

    template<class Traits>
    template<class Buffer>
    NT_FN base_file<Traits>::set_info(FILE_INFORMATION_CLASS info_class,
                                      Buffer&                buffer,
                                      ulong_t                info_size) const noexcept
    {
        IO_STATUS_BLOCK iosb;
        return LI_NT(NtSetInformationFile)(
            handle().get(), &iosb, ::std::addressof(buffer), info_size, info_class);
    }

    NTW_INLINE constexpr ulong_t normalize_attributes(file_options& options) noexcept
    {
        auto attr = options.attributes();
        if(!attr)
            attr = FILE_ATTRIBUTE_NORMAL;

        return attr;
    }
    template<bool Sync, class Options>
    NTW_INLINE constexpr ulong_t synchronize_options(Options& options) noexcept
    {
        auto opt = options.data().options;
        if constexpr(Sync)
            opt |= FILE_SYNCHRONOUS_IO_NONALERT;
        return opt;
    }

    template<bool Sync, class Options>
    NTW_INLINE constexpr ulong_t synchronize_access(Options& options) noexcept
    {
        auto access = options.data().access;
        if constexpr(Sync)
            access |= SYNCHRONIZE;
        return access;
    }

} // namespace ntw::io::detail

#undef NTW_BUILDER_OPTION
#undef NTW_FILE_OPTION
#undef NTW_FILE_ATTRIBUTE_OPTION
#undef NTW_PIPE_OPTION
