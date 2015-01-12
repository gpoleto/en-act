package it.unibz.enactmobile;

import it.unibz.decision.DatabaseManagement;
import it.unibz.decision.ExecutionType;
import it.unibz.decision.Module;
import it.unibz.decision.Record;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

//import com.example.hihi.FragmentPagerAdapter;
//import com.example.hihi.ImagePagerView;
//import com.example.hihi.Images;
//import com.example.hihi.Images_old;
//import com.example.hihi.MainActivity;
//import com.example.hihi.R;

import android.app.Activity;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.ViewPager;
import android.support.v4.view.ViewPager.OnPageChangeListener;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class EnActStart extends FragmentActivity implements
OnClickListener, OnPageChangeListener {
	private final static String TAG = "EnActStart";
	private String benchmark;
	private static String inputPath = "-/-"; 
	private static String replyAfterExecution = "Still debugging. Nothing done!";
	private Properties properties;
	private int SERVER_PORT;
	private String LOCAL_SERVER_ADDRESS;
	private String CLOUD_SERVER_ADDRESS;
	private String OFFLOADING;
	private String JNI;
	private RemoteServers SERVER;
	Module module = null;
	ExecutionType type = ExecutionType.None;
	boolean DEBUG = false;
	
	private Button btnImagePrevious, btnImageNext, btnApplyBW, btnSelectPic;
	private int position = 0, totalImage;
	private ViewPager viewPage;
	private ArrayList<Integer> itemData;
	private ArrayList<String> imagesList;
	private FragmentPagerAdapter adapter;
	//private Images_old imageId;
	//private Images images;
	//private String inputPath = "-/-";
	BitmapFactory.Options options = new BitmapFactory.Options();
	private static final int IMAGE_PICKER_SELECT = 999;
	

	//Native methods
	public native String multiplyMatricesFromFile(String path, String resultPath);
	public native String filterImage(String path, String resultPath);
	public native String meteorContestBenchmark();
	public native String mandelbrotBenchmark(int n);
	public native String spectralNormBenchmark(int n);
	
	static{
		System.loadLibrary("gnustl_shared");
		//System.loadLibrary("opencv_java");
		System.loadLibrary("operations");
		//System.loadLibrary("libjpeg");
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//TextView tv = new TextView(this);   
		
		initializeConfig();
		databaseSetup();
		///////////////////////////
		setContentView(R.layout.activity_image_pager_view);

		viewPage = (ViewPager) findViewById(R.id.viewPager);
		btnApplyBW = (Button) findViewById(R.id.btnApply_bw);
		
		imagesList = new ArrayList<String>();
		
		Intent intent = getIntent();
		inputPath = intent.getStringExtra(EnActMain.INPUT_PATH);
		//benchmark = intent.getStringExtra(EnActMain.BENCHMARK);
        Log.i(TAG, "input path: " + inputPath);
		imagesList.add(inputPath);
		
		adapter = new FragmentPagerAdapter(getSupportFragmentManager(), imagesList);
		
		viewPage.setAdapter(adapter);
		viewPage.setOnPageChangeListener(EnActStart.this);
		
		btnApplyBW.setOnClickListener(this);
		////////////////////////////
		
//		for(int i=1; i<=30; i++){
//			
//			Log.d(TAG,"Loop number: " + String.valueOf(i));
			
			//Has to be taken from the user input
			//Intent intent = getIntent();
			//benchmark = intent.getStringExtra(EnActMain.BENCHMARK);
			//String load = intent.getStringExtra(EnActMain.LOAD);
			
			//Log.i(TAG,"Benchmark selected: " + benchmark);
			
			//selectBenchmark(benchmark, load);
			
			try {
				Thread.sleep(500); //breath
			} catch (Exception e) { e.printStackTrace();	}
			
//		} // for loop
	
//		tv.setText(replyAfterExecution);
//		setContentView(tv);
		
		
		
				
//		System.exit(2057);
	}
	
	@Override
	public void onClick(View v) {
		if (v == btnApplyBW) {
			position++;
			String resultPath = null;
			benchmark = "BW";
			try {
				resultPath = processImage(inputPath);
			} catch (Exception e) {	e.printStackTrace(); }
			imagesList.add(resultPath);
			adapter.setNewList(imagesList);
			viewPage.setAdapter(adapter);
			viewPage.setCurrentItem(position);
		} 
	}
	
	@Override
	public void onPageScrollStateChanged(int arg0) {
	}
	
	@Override
	public void onPageScrolled(int arg0, float arg1, int arg2) {
	}
	
	@Override
	public void onPageSelected(int position) {
		Log.i(TAG, "Hello from onPageSelected()");
		this.position = position;
		//setPage(position);
	}

	private void initializeConfig() {
		properties = new Properties();
	      try {
			properties.load(getClass().getResourceAsStream("config.txt"));
		} catch (IOException e) { e.printStackTrace(); }
	      
	    properties.list(System.out);
	     
	    this.SERVER_PORT = Integer.parseInt(properties.getProperty("SERVER_PORT"));
	    this.LOCAL_SERVER_ADDRESS = properties.getProperty("LOCAL_SERVER_ADDRESS");
	    this.CLOUD_SERVER_ADDRESS = properties.getProperty("CLOUD_SERVER_ADDRESS");
//	    this.OFFLOADING = properties.getProperty("OFFLOADING");
//	    this.JNI = properties.getProperty("JNI");
	    final String srv = properties.getProperty("SERVER");
	    this.SERVER = RemoteServers.valueOf(srv);
	    final String dbg = properties.getProperty("DEBUG");
	    if (dbg.equals("true"))
	    	this.DEBUG = true;
	    
	    
	}
	
	private void databaseSetup() {
		
		DatabaseManagement db = new DatabaseManagement(this);
		///////DELETE next two lines in the future. Needed to re-populate the DB.
        SQLiteDatabase database = db.getWritableDatabase();
        db.onUpgrade(database,1,2);

//
//        Toast toast2 = Toast.makeText(MainActivity.this,"DB should have been created",Toast.LENGTH_LONG);
//        toast2.show();

        /*bar = (SeekBar) findViewById(R.id.bar);
        bar.setMax(10*1024);
        barInfo = (TextView) findViewById(R.id.barStatus);
        bar.setOnSeekBarChangeListener(this);*/

        interactWithDb(db);
        printAll(db);

        //---> FROM HERE THE REAL DECISION MODULE ALGORITHM WILL START WORKING
        module = new Module(db);
        //              (filesize,effect)
        
		
	}
	
	public void interactWithDb(DatabaseManagement db) {
		String model = Build.MANUFACTURER + " " + Build.MODEL;
        db.addRecord(new Record(7,10,20,1,5,"BW", model));
        db.addRecord(new Record(10,9,15,2,9,"BW", model));
        db.addRecord(new Record(20,23,15,7,22,"BW", model));
        db.addRecord(new Record(22,23,14,10,509846,"BW", model));
        db.addRecord(new Record(22,23,14,10,1530458,"BW", model));
    }
	
	public void printAll(DatabaseManagement db) {
        List<Record> records = db.getAllRecords();

        for (Record rec : records) {
            String log = "Id: "+rec.getId()+" ,Java: " + rec.getJavaJoule() + " ,JNI: " + rec.getJNIJoule() + " ,Cloud:" +
                    rec.getCloudJoule() +  " ,Network: "+ rec.getNetworkJoule() + " ,size:" + rec.getFileSize()+ " Effect: " + rec.getEffect() +
                    " Phone model: " + rec.getPhoneModel();

            // Writing Records to log
            Log.d("DB: ", log);
        }
    }
	
	private void selectBenchmark(String benchmark, String load) {
		if (benchmark.equals("matrices")){
			Log.i(TAG, "Matrix multiplication selected");					
			inputPath = load;
			Log.i(TAG,"PATH to matrices: " + inputPath);
			try {
				replyAfterExecution = multiplyMatrices(inputPath);
			} catch (Exception e) { e.printStackTrace();}
			
			Log.i(TAG, "Matrix multiplication finish");
			
		} else if(benchmark.equals("image")){
				Log.i(TAG, "Image processing selected");
				inputPath = load;
				Log.i(TAG,"PATH to matrices: " + inputPath);
				try {
					replyAfterExecution = processImage(inputPath);
				} catch (Exception e) { e.printStackTrace(); }
				Log.i(TAG, "Image processing finish");		
		} else {
				Log.e(TAG, "Invalid benchmark selection");
		}
	}
	
	public String connectToServer(String ip, int port, RemoteServers server) throws Exception{
		switch(server) {
			case LOCAL: new ThreadLocalOffload(inputPath, LOCAL_SERVER_ADDRESS, SERVER_PORT, benchmark).execute("").get(); break;
			case CLOUD: CloudConnection conn = new CloudConnection();
						conn.offloadToCloud(inputPath, new URL(CLOUD_SERVER_ADDRESS));
		}
		
		return "Fix connectToServer() to return a String!!!";
	}
	
	public String multiplyMatrices(String pathToMatrices) throws Exception {
		
		File file = new File(pathToMatrices);
		if (OFFLOADING.equals("true")) { //If the file is smaller than 200 Bytes
			Log.i(TAG, "File.length(): " + file.length() + ". Big matrices. Going to offload");
			replyAfterExecution = connectToServer(LOCAL_SERVER_ADDRESS, SERVER_PORT, SERVER);
			Log.i(TAG, "Reply from server: " + replyAfterExecution);
		} else {
			Log.i(TAG, "File.length(): " + file.length() + ". Small matrices. Going to call JNI functions");
			replyAfterExecution = multiplyMatricesFromFile(pathToMatrices, Environment.getExternalStorageDirectory() + "/enact_input/results/");
		}
		
		return replyAfterExecution;
	}
	
	public String processImage(String pathToImage) throws Exception {
		File file = new File(pathToImage);
		//type = module.selectExecution((int)file.length(),null);
		type = module.selectExecution( (int)file.length(), benchmark );
		
		//if (OFFLOADING.equals("true")) { //If the file is smaller than 200 Bytes
		if (type == ExecutionType.Offload) {
			Log.i(TAG, "File.length(): " + file.length() + ". Big image. Going to offload");
			replyAfterExecution = connectToServer(LOCAL_SERVER_ADDRESS, SERVER_PORT, SERVER);
			Log.i(TAG, "Reply from server: " + replyAfterExecution);
		} else {	
			//if (JNI.equals("true")) {
			if (type == ExecutionType.JNI) {
				Log.i(TAG, "File.length(): " + file.length() + ". Small image. Going to call JNI functions");
				replyAfterExecution = filterImage(pathToImage, Environment.getExternalStorageDirectory() + "/enact_input/results/");
			} else {
				if (type == ExecutionType.Java) {
					Log.i(TAG, "File.length(): " + file.length() + ". Small image. Going to local Java functions");
					replyAfterExecution = ImageEffects.effectGrayscale(pathToImage, Environment.getExternalStorageDirectory() + "/enact_input/results/");
				} else {
					Log.e(TAG, "Execution type was not selected.");
				}
			}
		}
		
		return replyAfterExecution;
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.en_act_start, menu);
		return true;
	}
	
	public void quit(View view){
		System.exit(2057);
	}

}
