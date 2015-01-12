package it.unibz.decision;

/**
 * This class represents a record object in the DB
 */
public class Record {

    private int _id;
    private int JavaJoule;
    private int JNIJoule;
    private int CloudJoule;
    private int NetworkJoule;
    private int fileSize;
    private String effect;
    private String phoneModel;

    public Record(){}

    public Record(int java,int jni,int cloud,int network,int size,String effect,String phoneModel) {
        this.JavaJoule = java;
        this.JNIJoule = jni;
        this.CloudJoule = cloud;
        this.NetworkJoule = network;
        this.fileSize = size;
        this.effect = effect;
        this.phoneModel = phoneModel;
    }

    public int getId() { return this._id;}

    public int getJavaJoule() {
        return this.JavaJoule;
    }

    public int getJNIJoule() {
        return this.JNIJoule;
    }

    public int getCloudJoule() {
        return this.CloudJoule;
    }

    public int getNetworkJoule() { return this.NetworkJoule;}

    public int getFileSize() {
        return this.fileSize;
    }

    public String getEffect() { return this.effect;}

    public String getPhoneModel() { return this.phoneModel;}

    public void setId(int anId) { this._id = anId;}

    public void setJavaJoule(int aJavaJoule) {
        this.JavaJoule = aJavaJoule;
    }

    public void setJNIJoule(int aJNIJoule) {
        this.JNIJoule = aJNIJoule;
    }

    public void setCloudJoule(int aCloudJoule) {
        this.CloudJoule = aCloudJoule;
    }

    public void setNetworkJoule(int aNetworkJoule) { this.NetworkJoule = aNetworkJoule; }

    public void setFileSize(int aFileSize) {
        this.fileSize = aFileSize;
    }

    public void setEffect(String anEffect) {this.effect = anEffect;}

    public void setPhoneModel(String aPhoneModel) { this.phoneModel = aPhoneModel;}

}
