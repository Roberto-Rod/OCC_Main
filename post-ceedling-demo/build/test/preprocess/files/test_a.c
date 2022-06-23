#include "src/a.h"
#include "C:/Ruby27-x64/lib/ruby/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp() {}

void tearDown() {}



void test_a(void) {

 int result = a();

 UnityAssertEqualNumber((UNITY_INT)((99)), (UNITY_INT)((result)), (

((void *)0)

), (UNITY_UINT)(10), UNITY_DISPLAY_STYLE_INT);

}
