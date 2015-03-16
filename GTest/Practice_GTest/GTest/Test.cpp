
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include<gtest/gtest.h>

#include "..\Practice_DesignPattern\Stereo3DRefactoring\Stereo3DHelper.h"

TEST( UseCase_CreateStereoModeTest, HandleNoneZeroInput)
{
   CStereo3DHelper  obj;
   int eStereoMode = _HDMI14;
   cout << "Set Stereo Mode: " << eStereoMode << "\n";
  
   EXPECT_EQ(eStereoMode, obj.constructStereo3DController(eStereoMode));
   EXPECT_EQ(1, obj.Query());
   EXPECT_EQ(1, obj.Enable());
   EXPECT_EQ(1, obj.Execute());
   EXPECT_EQ(eStereoMode, obj.ShowStereoInfo()); 
   EXPECT_EQ(1, obj.Disable());
}

TEST( UseCase_Interrupted, HandleNoneZeroInput)
{
   CStereo3DHelper  obj;
   int eStereoMode = _EMBEDDED_DISPLAYPORT;
   cout << "Set Stereo Mode: " << eStereoMode << "\n";
   EXPECT_EQ(eStereoMode, obj.constructStereo3DController(eStereoMode));cout << "\n";
   EXPECT_EQ(1, obj.Query());cout << "\n";
   EXPECT_EQ(1, obj.Enable());
   if (0) {
		  EXPECT_EQ(1, obj.Execute());cout << "\n";
   }
   else {
		 EXPECT_EQ(1, obj.Reset());
		 cout << "Stereo Mode Enabled Failed\n";
   }
   EXPECT_EQ(eStereoMode, obj.ShowStereoInfo()); cout << "\n";
   EXPECT_EQ(1, obj.Disable());cout << "\n";
   cout << "\n";
}
int _tmain(int argc,_TCHAR* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	cout << " ------ START ------ " << "\n";
	return RUN_ALL_TESTS();
}