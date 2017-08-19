package ocl;

public class OCL
{
	static
	{
		try
		{
			//System.load("/home/federico/GitKraken/TestTesi/Cpp/Out/libNativeTest.so");
			System.loadLibrary("NativeTest");
		}
		catch (UnsatisfiedLinkError e)
		{
			System.err.println("Native code library failed to load.\n" + e);
			System.exit(1);
		}
	}

	public native void sayHello();
}
