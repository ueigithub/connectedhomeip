/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *          Provides implementations for the CHIP logging functions
 *          on the Ameba platform.
 */
/* this file behaves like a config.h, comes first */
#include <platform/logging/LogV.h>

#include <core/CHIPConfig.h>
#include <support/logging/Constants.h>

#include <stdio.h>

#ifdef LOG_LOCAL_LEVEL
#undef LOG_LOCAL_LEVEL
#endif

namespace chip {
namespace Logging {
namespace Platform {

#if 1 //////// added by Minchun
static uint8_t m_logLevel = 3;
void LogSetLevel(uint8_t level)
{
    m_logLevel = level;
}
uint8_t  LogGetLevel(void)
{
    return m_logLevel;
}

void LogV(const char * module, uint8_t category, const char * msg, va_list v)
{
    char tag[11];

    if (m_logLevel == 0) return;

    snprintf(tag, sizeof(tag), "chip[%s]", module);
    tag[sizeof(tag) - 1] = 0;

    char formattedMsg[CHIP_CONFIG_LOG_MESSAGE_MAX_SIZE];
    vsnprintf(formattedMsg, sizeof(formattedMsg), msg, v);

    switch (category)
    {
    case kLogCategory_Error:
        if (m_logLevel >= 1) printf("%s %s\r\n", tag, formattedMsg);
        break;
    case kLogCategory_Progress:
    default:
        if (m_logLevel >= 2) printf("%s %s\r\n", tag, formattedMsg);
        break;
    case kLogCategory_Detail:
        if (m_logLevel >= 3) printf("%s %s\r\n", tag, formattedMsg);
        break;
    }
}
#else //////// added by Minchun
void LogV(const char * module, uint8_t category, const char * msg, va_list v)
{
    char tag[11];

    snprintf(tag, sizeof(tag), "chip[%s]", module);
    tag[sizeof(tag) - 1] = 0;

    char formattedMsg[CHIP_CONFIG_LOG_MESSAGE_MAX_SIZE];
    vsnprintf(formattedMsg, sizeof(formattedMsg), msg, v);

    switch (category)
    {
    case kLogCategory_Error:
        printf("%s %s\r\n", tag, formattedMsg);
        break;
    case kLogCategory_Progress:
    default:
        printf("%s %s\r\n", tag, formattedMsg);
        break;
    case kLogCategory_Detail:
        printf("%s %s\r\n", tag, formattedMsg);
        break;
    }
}

#endif //////// added by Minchun
} // namespace Platform
} // namespace Logging
} // namespace chip
