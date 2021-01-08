// ============================================================================
// <copyright file="main.cpp" company="VRK">
//     Copyright (c) ABB 2020. All rights reserved.
// </copyright>
// ============================================================================

// ============================================================================
// Local includes, e.g. files in the same folder, typically corresponding declarations.


// ============================================================================
// System includes, e.g. STL, Library headers, ...

#include <gtest/gtestFramework.h>


// ============================================================================
// Definitions

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);  // This allows the user to override the flag on the command line.
	
	return RUN_ALL_TESTS();
}