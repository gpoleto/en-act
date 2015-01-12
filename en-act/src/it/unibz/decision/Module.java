package it.unibz.decision;

import android.os.Build;
import android.util.Log;

/**
 * Author: Giuseppe Aina
 *
 * This will be the class for the decision module at computation
 * time. Based on some specific parameters it will decide either to offload
 * or to compute the work locally on the phone (Java or Jni).
 * In order to achieve this goal also an external API is used.
 */
public class Module {

    // size of the file which should be either offloaded or computed locally

    DatabaseManagement db;

    public Module(DatabaseManagement db) {
        this.db = db;
    }

    // the real algorithm
    public ExecutionType selectExecution(int fileSize, String effect) {
    	ExecutionType type = ExecutionType.None;
        Record theRecord = db.getWorkingRecord(fileSize, effect, new String(Build.MANUFACTURER + " " + Build.MODEL));
        String log = "Id: "+theRecord.getId()+" ,Java: " + theRecord.getJavaJoule() + " ,JNI: " + theRecord.getJNIJoule() + " ,Cloud:" +
                theRecord.getCloudJoule() + " ,network:" + theRecord.getNetworkJoule() + " ,size:" + theRecord.getFileSize();
        // Writing the Records to log
        Log.d("DB: ", log);

        if(theRecord.getCloudJoule() < theRecord.getJavaJoule() && theRecord.getCloudJoule() < theRecord.getJNIJoule()) {
            int network = theRecord.getNetworkJoule();
            if(theRecord.getCloudJoule() + network < theRecord.getJavaJoule() && theRecord.getCloudJoule() + network < theRecord.getJNIJoule()) {
               Log.d("Winner","Offload");
               type = ExecutionType.Offload;
            }else {
                if(theRecord.getJavaJoule() < theRecord.getJNIJoule()) {
                    Log.d("Winner","Go for java");
                    type = ExecutionType.Java;
                }else { 
                	Log.d("Winner","Go for jni");
                	type = ExecutionType.JNI;
                }
            }
        } else {
            if(theRecord.getJavaJoule() < theRecord.getJNIJoule()) {
                Log.d("Winner","Go for javaaaaaa");
                type = ExecutionType.Java;
	        } else { 
	        	Log.d("Winner","Go for jni");
	        	type = ExecutionType.JNI;
        	}
        }
        
        return type;
    }


    /*public StringBuffer estimateEnergyConsumption() {
        //acquire EnergyEstimates for all technologies
        Vector<EnergyEstimate> currentEstimates = EnergyEstimator.estimateConsumption(upload, download);

        //print energyEstimates for all technologies
        StringBuffer buffer = new StringBuffer();
        for (EnergyEstimate energyEstimate : currentEstimates) {
            buffer.append(energyEstimate.getTechnology() + ":\n");
            buffer.append("Min: " + energyEstimate.getMin() + " J\n");
            buffer.append("Mean: " + energyEstimate.getMean() + " J\n");
            buffer.append("Max: " + energyEstimate.getMax() + " J\n");
        }

        return buffer;
        //txtEnergyEstimates.setText(buffer.toString());
    }*/


}
