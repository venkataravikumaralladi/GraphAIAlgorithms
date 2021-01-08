// ============================================================================
// This document contains confidential and proprietary information of ABB
// and may be protected by patents, trademarks, copyrights, trade secrets,
// and/or other relevant state, federal, and foreign laws.  Its receipt or
// possession does not convey any rights to reproduce, disclose its contents,
// or to manufacture, use or sell anything contained herein. Forwarding,
// reproducing, disclosing or using without specific written authorization of
// ABB is strictly forbidden.
// ============================================================================
// <copyright file="DynamicLogger.cpp" company="ABB">
//     Copyright (c) ABB 2019. All rights reserved.
// </copyright>
// ============================================================================


// ============================================================================
// Local includes, e.g. files in the same folder, typically corresponding declarations.
#include "../Common/ModbusTCPErrorDef.h"
#include "../Common.h"
#include "DynamicLogger.h"
// ============================================================================
// System includes, e.g. STL, Library headers, ...


// ============================================================================
// Other includes with complete path as Layer/Component/...


// ============================================================================
// Definitions
using namespace NCP;

namespace ModbusTCPSigTrans
{

void DynamicLogger::UpdateTraceSettings(bool isTraceOn, LogTraceLevelVal logTraceLevel, int traceClasses)
{
	m_TraceIsOn = isTraceOn;
	m_TraceLevel = logTraceLevel;
	m_TraceClasses = traceClasses;
}

}; // namespace ModbusTCPSigTrans