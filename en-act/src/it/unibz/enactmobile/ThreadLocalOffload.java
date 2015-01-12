package it.unibz.enactmobile;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import android.os.AsyncTask;
import android.os.Build;
import android.os.Environment;
import android.util.Log;

public class ThreadLocalOffload extends AsyncTask<String, String, String> {
	
	private final static String TAG = "ThreadMatrixOffload";
	private Socket socket;
	private String inputFilename;
	private static String replyFromServer = "Failure";
	private String localServerAddress;
	private int port;
	private String benchmark;
	
	public ThreadLocalOffload(String inputFilename, String localAddress, int p, String benchmark) {
		localServerAddress = localAddress;
		port = p;
		this.inputFilename = inputFilename;
		this.benchmark = benchmark;
	}
	       
    //@Override
    //Must be implemented!!! Actually does computations in another thread ;)        
    protected String doInBackground(String... params) {
    	
    	String resultFilepath = "";
    	try {
			resultFilepath = sendAndReceiveFile(inputFilename, localServerAddress, port);
		} catch (UnknownHostException e) {				
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}    	
    	
    	Log.i("doInBackground()","No more stmts in doInBackground()");
    	
        return resultFilepath;
    }
    
    //Runs on the UI thread after doInBackground()
    protected void onPostExecute(String response) {	    	
    	//Debugging
    	replyFromServer = response;
    	Log.d(TAG, "Thread post-execution...");
    }
    
    public String sendAndReceiveFile(String inputFilename, String address, int port) throws UnknownHostException, IOException {
    	
    	File myFile = new File(inputFilename);

    	//==| Send benchmark string    	
    	this.socket = new Socket(address, port);
    	int count;
    	byte[] buffer = new byte[1024];

    	OutputStream out = socket.getOutputStream();
    	byte[] benchmarkBytes = benchmark.getBytes("UTF-8");
    	out.write(benchmarkBytes);
    	out.flush();
    	Log.i(TAG, "alive");
    	
    	try {
			Thread.sleep(300);
		} catch (InterruptedException e) { e.printStackTrace();	}
    	
    	
    	// Send file
    	out = socket.getOutputStream();
    	BufferedInputStream in = new BufferedInputStream(new FileInputStream(myFile));
    	while ((count = in.read(buffer)) > 0) {
    	     out.write(buffer, 0, count);
    	     out.flush();
    	}
    	socket.close();
    	out.close();
    	in.close();
    	
    	
    	//==| Receive the result
    	String resultFilepath = "";	 
    	if (benchmark.equals("matrices")) {
	    	if ("sdk".equals(Build.MODEL)) 
	    		resultFilepath = Environment.getExternalStorageDirectory() + "/" + benchmark + "_result_offloading.txt";
	    	else
	    		resultFilepath = Environment.getExternalStorageDirectory() + "/enact_input/results/" + benchmark + "_result_offloading.txt";
    	} else { 
    		if (benchmark.equals("image")) {
		    		if ("sdk".equals(Build.MODEL)) 
			    		resultFilepath = Environment.getExternalStorageDirectory() + "/" + benchmark + "_result_offloading.png";
			    	else
			    		resultFilepath = Environment.getExternalStorageDirectory() + "/enact_input/results/" + benchmark + "_result_offloading.png";
    			}
    		
    	}
    	
    	ServerSocket srv_socket = new ServerSocket(8888);
    	Log.i("sendAndReceiveFile()", "I'm waiting on:" + srv_socket);
    	Socket in_socket = srv_socket.accept();
    	FileOutputStream fos = new FileOutputStream(resultFilepath);
    	BufferedOutputStream bos = new BufferedOutputStream(fos);
    	byte[] receive_buffer = new byte[1024];
    	int receive_count;
    	InputStream receive_in = in_socket.getInputStream();
    	while((receive_count=receive_in.read(receive_buffer)) > 0){
    	    fos.write(receive_buffer, 0, receive_count);
    	}
    	receive_in.close();
    	bos.close();
    	fos.close();
    	in_socket.close();
    	srv_socket.close();	    	
    	Log.i(TAG, "send and receive done!");
    	
    	return resultFilepath;
    }
}
	