package it.unibz.decision;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.content.Context;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

/**
 * Class for creating the database scheme and establish connections to it
 * every time data is needed for deciding weather to offload or to run the task
 * locally.
 * A SQLite database is employed since it suits in low memory device such as a smart phone
 */
public class DatabaseManagement extends SQLiteOpenHelper {

    private static final int DATABASE_VERSION = 1;
    private static final String  DATABASE_NAME = "enact_energy_db";
    private static final String DATABASE_TABLE = "consumption";
    private static final String KEY_ID = "id";
    private static final String JAVA_JOULE = "java_joule";
    private static final String JNI_JOULE = "jni_joule";
    private static final String CLOUD_JOULE = "cloud_joule";
    private static final String NETWORK_JOULE = "network_joule";
    private static final String FILE_SIZE = "file_size";
    private static final String EFFECT = "effect";
    private static final String PHONE_MODEL = "phone_model";


    public DatabaseManagement(Context context) {
        super(context,DATABASE_NAME,null,DATABASE_VERSION);
    }


    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        String CREATE_CONSUMPTION_TABLE = "CREATE TABLE " + DATABASE_TABLE + "("
                + KEY_ID + " INTEGER PRIMARY KEY," + JAVA_JOULE + " INTEGER,"
                + JNI_JOULE + " INTEGER," + CLOUD_JOULE + " INTEGER," + NETWORK_JOULE + " INTEGER,"
                + FILE_SIZE + " INTEGER," + EFFECT + " TEXT," + PHONE_MODEL + " TEXT" + ")";
        Log.d("create",CREATE_CONSUMPTION_TABLE);
        sqLiteDatabase.execSQL(CREATE_CONSUMPTION_TABLE);
        Log.d("DB","Sono dentro");
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i2) {
        sqLiteDatabase.execSQL("DROP TABLE IF EXISTS " + DATABASE_TABLE);
        onCreate(sqLiteDatabase);
        Log.d("DB","Siamo nell onUpgrade");
    }

    //add a new record into the db
    public void addRecord(Record record){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(JAVA_JOULE,record.getJavaJoule());
        values.put(JNI_JOULE,record.getJNIJoule());
        values.put(CLOUD_JOULE,record.getCloudJoule());
        values.put(NETWORK_JOULE,record.getNetworkJoule());
        values.put(FILE_SIZE,record.getFileSize());
        Log.d("Effect",record.getEffect());
        values.put(EFFECT, record.getEffect());
        values.put(PHONE_MODEL,record.getPhoneModel());

        db.insert(DATABASE_TABLE,null,values);
        db.close();
    }
    
    public Record getWorkingRecord(int MB, String effect, String phone) {
        SQLiteDatabase db = this.getReadableDatabase();
        String query = "SELECT * FROM " + DATABASE_TABLE + " WHERE " + PHONE_MODEL + " = '" + phone + "' and " + EFFECT + " = '" + effect + "' order by file_size";
        Cursor cursor = db.rawQuery(query,null);
        Record record = null,prev = null;

        
        
        if(cursor != null) {
            cursor.moveToFirst();
            prev = makeRecord(cursor);
            if (prev.getFileSize() == MB)
            	return prev;
            //if (prev.getFileSize() <= MB) {
            else if (prev.getFileSize() < MB) {
            	
            	while (cursor.moveToNext()) {
	            	record = makeRecord(cursor);
	            	if (record.getFileSize() == MB) {
	            		return record;	            		
	            	} else if (record.getFileSize() > MB) {
	            		record = makeRecord(cursor);
	            		cursor.moveToPrevious();
	            		prev = makeRecord(cursor);
	            		Record avg = makeAverageRecord(prev, record, MB);
	            		addRecord(avg);
	            		return avg;
	            	}
	            } ;
	            
            } else { // else insert prev con MB and return prev
            	prev.setFileSize(MB);
            	addRecord(prev);
            	return prev;
            }
           
        } else { // else insert the new file_size row
        	
        }

        return record;
    }

    public Record makeAverageRecord(Record a, Record b, int size) {
    	Record avg = new Record();
    	
    	avg.setCloudJoule((a.getCloudJoule() + b.getCloudJoule())/2);
    	avg.setJavaJoule((a.getJavaJoule() + b.getJavaJoule())/2);
    	avg.setJNIJoule((a.getJNIJoule() + b.getJNIJoule())/2);
    	avg.setNetworkJoule((a.getNetworkJoule() + b.getNetworkJoule())/2);
    	avg.setEffect(a.getEffect());
    	avg.setFileSize(size);
    	avg.setPhoneModel(a.getPhoneModel());
    	
    	return avg;
    }
    
    public Record makeRecord(Cursor cursor) {
    	Record record = new Record();
    	record.setId(Integer.parseInt(cursor.getString(0)));
        record.setJavaJoule(Integer.parseInt(cursor.getString(1)));
        record.setJNIJoule(Integer.parseInt(cursor.getString(2)));
        record.setCloudJoule(Integer.parseInt(cursor.getString(3)));
        record.setNetworkJoule(Integer.parseInt(cursor.getString(4)));
        record.setFileSize(Integer.parseInt(cursor.getString(5)));
        record.setEffect(cursor.getString(6));
        record.setPhoneModel(cursor.getString(7));
        
        return record;
    }
    
    public List<Record> getAllRecords() {
        List<Record> records = new ArrayList<Record>();
        String select = "SELECT * FROM " + DATABASE_TABLE;
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor cursor = db.rawQuery(select,null);

        if(cursor.moveToFirst()) {
            do {
                Record record = new Record();
                record.setId(Integer.parseInt(cursor.getString(0)));
                record.setJavaJoule(Integer.parseInt(cursor.getString(1)));
                record.setJNIJoule(Integer.parseInt(cursor.getString(2)));
                record.setCloudJoule(Integer.parseInt(cursor.getString(3)));
                record.setNetworkJoule(Integer.parseInt(cursor.getString(4)));
                record.setFileSize(Integer.parseInt(cursor.getString(5)));
                record.setEffect(cursor.getString(6));
                record.setPhoneModel(cursor.getString(7));
                records.add(record);
            }while(cursor.moveToNext());

        }
        return records;
    }
    public int getRecordCount() {return 0;}
    public int updateRecord() {return 0;}
    public void deleteRecord(Record record) {}

}
