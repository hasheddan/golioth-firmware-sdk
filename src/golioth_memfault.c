/*
 * Copyright (c) 2023 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "golioth_coap_client.h"
#include "golioth_sys.h"

#include "golioth_memfault.h"

#include <memfault/components.h>

#define CONFIG_GOLIOTH_MFLT_CHUNK_SIZE 1024

#define CONFIG_GOLIOTH_MFLT_UPLOAD_INTERVAL_SECONDS 5

static void handle_mflt_timer(golioth_sys_timer_t timer, void* arg)
{
    golioth_sys_timer_start(timer);
    golioth_memfault_upload_now((golioth_client_t) arg);
}

int golioth_memfault_upload_now(golioth_client_t client)
{
    uint8_t buf[CONFIG_GOLIOTH_MFLT_CHUNK_SIZE];
    size_t buf_len = sizeof(buf);
    while (memfault_packetizer_get_chunk(buf, &buf_len))
    {
    	golioth_coap_client_set(client,
    				"mflt",
    				"",
    				COAP_MEDIATYPE_APPLICATION_OCTET_STREAM,
    				buf,
    				buf_len,
    				NULL,
    				NULL,
    				false,
    				GOLIOTH_WAIT_FOREVER);
    }

    return 0;
}

int golioth_memfault_timer_start(golioth_client_t client)
{
    golioth_sys_timer_config_t timer_config = {
    	.name = "mflt_upld_tmr",
    	.expiration_ms = CONFIG_GOLIOTH_MFLT_UPLOAD_INTERVAL_SECONDS * 1000,
    	.fn = handle_mflt_timer,
    	.user_arg = client,
    };
    golioth_sys_timer_t timer = golioth_sys_timer_create(timer_config);
    golioth_sys_timer_start(timer);

    return 0;
}
