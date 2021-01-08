// ============================================================================
// This document contains confidential and proprietary information of ABB
// and may be protected by patents, trademarks, copyrights, trade secrets,
// and/or other relevant state, federal, and foreign laws.  Its receipt or
// possession does not convey any rights to reproduce, disclose its contents,
// or to manufacture, use or sell anything contained herein.  Forwarding,
// reproducing, disclosing or using without specific written authorization of
// ABB is strictly forbidden.
// ============================================================================
// <copyright file="gtestFramework.h.h" company="ABB">
//     Copyright (c) ABB 2017. All rights reserved.
// </copyright>
// ============================================================================

#pragma once

// The only include needed in gtest based tests.

// ============================================================================
// Includes
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>


// ============================================================================
// Declarations

// Set a test id
#define TEST_ID(desc)               RecordProperty("testId", desc)
// Set a test description
#define TEST_DESCRIPTION(desc)      RecordProperty("testDescription", desc)
// Describe the test setup
#define TEST_SETUP(desc)            RecordProperty("testSetup", desc)
// Set an expected result.
#define TEST_EXPECTED_RESULT(desc)  RecordProperty("testExpectedResult", desc)
