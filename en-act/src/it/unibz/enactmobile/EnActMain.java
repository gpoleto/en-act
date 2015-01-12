package it.unibz.enactmobile;

import java.io.FileOutputStream;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.text.format.Time;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.provider.MediaStore;

public class EnActMain extends Activity  implements OnClickListener {
	
	private int IMAGE_PICKER_SELECT = 999;
	private Button btnSelectPic;
	private String TAG = "MainActivity";
	public static String INPUT_PATH = "<no path>";
//	public static String BENCHMARK = "<no benchmark>";
	private String inputPath = "-/-";
//	private String benchmark = "-/-";
	
	private Button btnTakePhoto;
    //ImageView imgTakenPhoto;
    private static final int CAM_REQUREST = 1313;
    

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		btnSelectPic = (Button) findViewById(R.id.btnSelectPic);
		btnTakePhoto = (Button) findViewById(R.id.btnTakePic);
		
		btnSelectPic.setOnClickListener(this);
		btnTakePhoto.setOnClickListener(this);
		
        Log.i(TAG, "onCreate() finished.");
		

	}
	
	@Override
	public void onClick(View v) {
		Log.i(TAG,"Something is clicked.");
		if (v == btnSelectPic) {
			Intent i = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI); 
			startActivityForResult(i, IMAGE_PICKER_SELECT);
		} else if (v == btnTakePhoto) {
			Log.i(TAG,"\"Take a picture\" button was cliked.");
			//benchmark = "BW";
			Intent cameraIntent = new Intent(android.provider.MediaStore.INTENT_ACTION_STILL_IMAGE_CAMERA);
            startActivityForResult(cameraIntent, CAM_REQUREST);
		}
		
		Log.i(TAG,"Clicking is over.");
	}
	
	@Override	
	public void onActivityResult(int requestCode, int resultCode, Intent data) { 
		
		Log.i(TAG,"Hello from onActivityResult!");
		
		super.onActivityResult(requestCode, resultCode, data);
	    		
	     if (requestCode == IMAGE_PICKER_SELECT && resultCode == RESULT_OK && null != data) {
	         Uri selectedImage = data.getData();
	         String[] filePathColumn = { MediaStore.Images.Media.DATA };
	 
	         Cursor cursor = getContentResolver().query(selectedImage,
	                 filePathColumn, null, null, null);
	         cursor.moveToFirst();
	 
	         int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
	         // The String inputPath contains the path of selected Image
	         inputPath = cursor.getString(columnIndex);
	         Log.i(TAG + " / onActivityResult()", "The path of the picture just selected: " + inputPath);
	         
	         cursor.close();
	         
	         Intent intent = new Intent(this, EnActStart.class);	         
	         intent.putExtra(INPUT_PATH, inputPath);
	         //intent.putExtra(BENCHMARK, benchmark);
	         startActivity(intent);
	         
	         // String picturePath contains the path of selected Image
	     }
	     
	     if (requestCode == CAM_REQUREST && resultCode == RESULT_OK && data.getExtras().get("data") != null) {
	            Bitmap thumbnail = (Bitmap) data.getExtras().get("data");
	            Log.i(TAG, "thumbnail width: " + thumbnail.getWidth() + " / " + thumbnail.getHeight());
	            //Bitmap thumbnail_new = gray2(thumbnail);
	            Log.d(TAG, "und!????");
	            //imgTakenPhoto.setImageBitmap(thumbnail_new);
	            inputPath = saveBitmap(thumbnail);
	            
	            Intent intent = new Intent(this, EnActStart.class);	         
		        intent.putExtra(INPUT_PATH, inputPath);
		        startActivity(intent);
	     }
	     
//	     if (requestCode == CAM_REQUREST && resultCode == RESULT_CANCELED ) {
//	    	 
//	     }
	}
	
	public String saveBitmap(Bitmap bm)
    {
		String mBaseFolderPath = "";
        try
        {
            mBaseFolderPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/DCIM/Camera/";
            Time now = new Time();
            now.setToNow();
            String time = String.valueOf(now.year) + String.valueOf(now.month+1) + String.valueOf(now.monthDay) + "_" + String.valueOf(now.hour) + String.valueOf(now.minute) + String.valueOf(now.second);
            Log.i(TAG, "The time now is: " + time);
            mBaseFolderPath += "IMG_enact_" + time + ".jpg";

            Log.i(TAG, "bm width: " + bm.getWidth() + " / height: " + bm.getHeight());
            
            FileOutputStream stream = new FileOutputStream(mBaseFolderPath);
            bm.compress(Bitmap.CompressFormat.JPEG, 100, stream);
            Log.i(TAG, "bm width: " + bm.getWidth() + " / height: " + bm.getHeight());
            stream.flush();
            stream.close();
        }
        catch(Exception e)
        {
            Log.e("Could not save", e.toString());
        }
        
        return mBaseFolderPath;
    }
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {

		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.en_act_main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
}


//package it.unibz.enactmobile;
//
//
//import android.app.Activity;
//import android.os.Build;
//import android.os.Environment;
//import android.util.Log;
//
//import android.content.*;
//import android.view.*;
//import android.widget.*;
//import android.os.Bundle;
//
//
//public class EnActMain extends Activity {
//	
//	
//	public final static String BENCHMARK = "a";
//	public final static String LOAD = "b";
//	public static String INPUT_PATH = "<no path>"; 
//	public static String benchmark;
//	public static String load;
//	
//	private final static String TAG = "EnActMain";
//	
//	@Override
//	protected void onCreate(Bundle savedInstanceState) {
//		super.onCreate(savedInstanceState);
//		
//		if ("sdk".equals(Build.MODEL))
//			Log.v(TAG, "Developer_Android application is running on: Emulator");
//		else
//			Log.v(TAG, "En-Act Mobile application is running on: " + Build.MANUFACTURER + " " + Build.MODEL);
//		setContentView(R.layout.activity_en_act_main);
//	}
//		
//	@Override
//	public boolean onCreateOptionsMenu(Menu menu) {
//		// Inflate the menu; this adds items to the action bar if it is present.
//		getMenuInflater().inflate(R.menu.en_act_main, menu);
//		return true;
//	}
//
//	public void onRadioButtonClicked(View view) {
//		
//		boolean checked = ((RadioButton) view).isChecked();
//		
//		final int i = 0;
//	    
//	    // Check which radio button was clicked
//	    switch(view.getId()) {
//	        case R.id.radio_matrix:
//	            if (checked)
//	                benchmark = "matrices";
//	            break;
//	        case R.id.radio_image:
//	            if (checked)
//	                benchmark = "image";
//	            break;	        
//	    }
//		
//	}
//	
//	public void onRadioClicked(View view) {
//		
//		boolean checked = ((RadioButton) view).isChecked();
//	    
//	    // Check which radio button was clicked
//	    switch(view.getId()) {
//	        case R.id.radio_level1:
//	            if (checked)
//	                load = "1";
//	            break;
//	        case R.id.radio_level2:
//	            if (checked)
//	            	load = "2";
//	            break;
//	        case R.id.radio_level3:
//	            if (checked)
//	            	load = "3";
//	            break;
//	        case R.id.radio_level4:
//	            if (checked)
//	            	load = "4";
//	            break;
//	        case R.id.radio_level5:
//	            if (checked)
//	            	load = "5";
//	            break;
//	    }
//		
//	}
//
//	public void runBenchmark(View view) {
//		
//		Intent intent = new Intent(this, EnActStart.class);
//		
//		int iload = Integer.parseInt(load);
//		
//		Log.i(TAG, "Environment.getExternalStorageDirectory(): " + Environment.getExternalStorageDirectory());
//		Log.i(TAG, "Environment.getRootDirectory(): " + Environment.getRootDirectory());
//		
//		switch(iload) {
//			case 1:
//					if (benchmark.equals("matrices")) {// || benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;						
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/Matrices_small.txt";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/Matrices_small.txt";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					if (benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/icon.png";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/icon.png";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					break;
//			
//			case 2:
//					if (benchmark.equals("matrices")) {// || benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/Matrices_20x30.txt";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/Matrices_20x30.txt";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					if (benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/kolibri.png";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/kolibri.png";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					break;
//				
//			case 3:
//					if (benchmark.equals("matrices")) {// || benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/Matrices_200x300.txt";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/Matrices_200x300.txt";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					if (benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
////							pathToMatrices = Environment.getExternalStorageDirectory() + "/beppe_avatar.jpg";
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/Icet.bmp";
////							pathToMatrices = Environment.getExternalStorageDirectory() + "/debug.bmp";
//				    	else
////				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/beppe_avatar.jpg";
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/Icet.bmp";
////				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/debug.bmp";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					break;
//					
//			case 4:
//					if (benchmark.equals("matrices")) {// || benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/Matrices_350x700.txt";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/Matrices_350x700.txt";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					if (benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/Boston_City_Flow.jpg";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/Boston_City_Flow.jpg";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					break;
//					
//			case 5:
//					if (benchmark.equals("matrices")) {// || benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/Matrices_big.txt";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/Matrices_big.txt";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					if (benchmark.equals("image")) {
//						intent.putExtra(BENCHMARK, benchmark);
//						String pathToMatrices;
//						if ("sdk".equals(Build.MODEL)) 
//							pathToMatrices = Environment.getExternalStorageDirectory() + "/beach.jpeg";
//				    	else
//				    		pathToMatrices = Environment.getExternalStorageDirectory() + "/enact_input/beach.jpeg";
//						intent.putExtra(LOAD,pathToMatrices);
//					}
//					
//					break;
//					
//			default:
//					System.out.println("Invalid Radio choice for Load");
//					break;
//		}		
//					
//		startActivity(intent);
//		
//	}
//	
//}
