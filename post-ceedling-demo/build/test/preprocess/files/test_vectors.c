#include "test/support/vector_helper.h"
#include "test/../src/vectors.h"
#include "C:/Ruby27-x64/lib/ruby/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp() {}

void tearDown() {}



void test_initVector() {

 vectorPtr vec = initVector(1, 2);

 do {if ((((vec)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(11))));}} while(0);

 UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((vec->x)), (

((void *)0)

), (UNITY_UINT)(12), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((vec->y)), (

((void *)0)

), (UNITY_UINT)(13), UNITY_DISPLAY_STYLE_INT);

 destroyVector(&vec);

 do {if ((((vec)) == 

((void *)0)

)) {} else {UnityFail( (((" Expected NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(15))));}} while(0);

}



void test_sumVectors() {

 vectorPtr vec1 = initVector(1, 2);

 vectorPtr vec2 = strToVector("3;4");

 do {if ((((vec1)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(21))));}} while(0);

 do {if ((((vec2)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(22))));}} while(0);

 vectorPtr sumVec = sumVectors(vec1, vec2);

 do {if ((((sumVec)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(24))));}} while(0);

 UnityAssertEqualNumber((UNITY_INT)((4)), (UNITY_INT)((sumVec->x)), (

((void *)0)

), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((6)), (UNITY_INT)((sumVec->y)), (

((void *)0)

), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT);

 destroyVector(&vec1);

 destroyVector(&vec2);

 destroyVector(&sumVec);

}



void test_cmp_vectors_equal() {

 vectorPtr vec1 = initVector(1, 2);

 vectorPtr vec2 = strToVector("1;2");

 do {if ((((vec1)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(35))));}} while(0);

 do {if ((((vec2)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(36))));}} while(0);

 int result = cmpVectors(vec1, vec2);

 UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (

((void *)0)

), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);

 destroyVector(&vec1);

 destroyVector(&vec2);

}



void test_cmp_vectors_different_y() {

 vectorPtr vec1 = initVector(1, 2);

 vectorPtr vec2 = strToVector("1;4");

 do {if ((((vec1)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(46))));}} while(0);

 do {if ((((vec2)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(47))));}} while(0);

 int result = cmpVectors(vec1, vec2);

 UnityAssertEqualNumber((UNITY_INT)((-2)), (UNITY_INT)((result)), (

((void *)0)

), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_INT);

 destroyVector(&vec1);

 destroyVector(&vec2);

}



void test_cmp_vectors_different_x() {

 vectorPtr vec1 = initVector(4, 2);

 vectorPtr vec2 = strToVector("1;2");

 do {if ((((vec1)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(57))));}} while(0);

 do {if ((((vec2)) != 

((void *)0)

)) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(58))));}} while(0);

 int result = cmpVectors(vec1, vec2);

 UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((result)), (

((void *)0)

), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT);

 destroyVector(&vec1);

 destroyVector(&vec2);

}
