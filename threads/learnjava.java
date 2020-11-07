import java.io.*;
import java.util.*;
import java.net.*;
public class ThreadsDemo1 extends thread{
	String mesg;
	int count;
/** Run does the work: print a message, "count" number of times */
	public void run( ) {
	while (count-- > 0) {
	println(mesg);
	try {
		Thread.sleep(100);
// 100 ms Running Code in a Different Thread |
	} catch (InterruptedException e) {
	return;
	}
	}
	println(mesg + " all done.");
	}
	void println(String s) {
	System.out.println(s);
	}
/**
	* Construct a ThreadsDemo1 object.
* @param m Message to display
* @param n How many times to display it
*/
	public ThreadsDemo1(String m, int n) {
		count = n;
		mesg = m;
		setName(m + " runner Thread");
}
/**
* Main program, test driver for ThreadsDemo1 class.
*/
	public static void main(String[] argv) {
// could say: new ThreadsDemo1("Hello from X", 10).run( );
// could say: new ThreadsDemo1("Hello from Y", 15).run( );
// But then it wouldn't be multi-threaded!
		new ThreadsDemo1("Hello from X", 10).start( );
		new ThreadsDemo1("Hello from Y", 15).start( );
	}
}

