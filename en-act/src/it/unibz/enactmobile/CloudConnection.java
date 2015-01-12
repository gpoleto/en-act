package it.unibz.enactmobile;

import java.io.File;
import java.net.URL;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpVersion;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.mime.HttpMultipartMode;
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.CoreProtocolPNames;
import org.apache.http.util.EntityUtils;

import android.os.AsyncTask;
import android.util.Log;

public class CloudConnection {
	
	private final String TAG = "CloudConnection";

public void offloadToCloud(String path, URL url) {
		
    	//Debugging
    	Log.d(TAG, "postURL: " + url.toString());

    	//new HttpClient
    	HttpClient httpClient = new DefaultHttpClient();
    	httpClient.getParams().setParameter(CoreProtocolPNames.PROTOCOL_VERSION, HttpVersion.HTTP_1_1);
    	 
    	//POST request header
    	HttpPost httpPost = new HttpPost(url.toString());

    	//Preparing the file to be attached to the POST request
    	File file = new File(path);
    	FileBody fileBody = new FileBody(file);

    	//Attaching the file to the POST request
    	MultipartEntity reqEntity = new MultipartEntity(HttpMultipartMode.BROWSER_COMPATIBLE);
    	reqEntity.addPart("uploadFile", fileBody);
    	httpPost.setEntity(reqEntity);

    	//New thread to be created since network tasks are considered as long operations to be executed in the main thread.
    	new SendFileToCloud(httpClient,httpPost).execute("");
		
	}

private class SendFileToCloud extends AsyncTask<String, String, HttpResponse> {
	
	private HttpClient httpclient;
	private HttpPost httppost;
	
	public SendFileToCloud(HttpClient client, HttpPost post) {
		httpclient = client;
		httppost = post;
	}
	       
    //@Override
    //Must be implemented!!! Actually does computations in another thread ;)        
    protected HttpResponse doInBackground(String... params) {
    	HttpResponse response = null;
        try {
            response = httpclient.execute(httppost);
            Log.d(TAG, "POST request is sent");
        } catch (Exception e) {e.printStackTrace(); }
        
        return response;
    }
    
    //Runs on the UI thread after doInBackground()
    protected void onPostExecute(HttpResponse response) {        	
    	
    	//Debugging
    	Log.d(TAG, "Thread post-execution");
        
    	HttpEntity resEntity = response.getEntity();

    	if (resEntity != null) {

        	String responseStr = "-/-";
			try {
				responseStr = EntityUtils.toString(resEntity).trim();
			} catch (Exception e) {	e.printStackTrace(); }
			
			//The response from the cloud server in HTML
        	Log.i(TAG, "=============================================================\n" +
        			responseStr + "\n" +
                  "=============================================================");
    	}
    	
    }
}

}
