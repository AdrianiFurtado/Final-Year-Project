#include<stdio.h>
#include<jni.h>

int add(int a, int b);

JNIEXPORT void JNICALL Java_javaP_say
(JNIEnv * env, jclass jobj, jstring js){

	//printf("number from java is %i\n", jx);
	//printf("Adding 5 to number from java\n");
	//int result = add(jx, 5);
	//return result;
	const char * jString;
	jString = (*env)->GetStringUTFChars(env, js, NULL);
	printf("%s \n", jString);


}


int add(int a, int b){

	return a+b;

}

