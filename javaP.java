
public class javaP{


	native static void say(String string);

	static{

		System.loadLibrary("cFile");

	}


	public static void main(String argc[]){

		int number;
		javaP call = new javaP();
		call.say("hello from C");

	}

}
