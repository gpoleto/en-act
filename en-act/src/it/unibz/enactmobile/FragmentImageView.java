package it.unibz.enactmobile;

import android.app.ProgressDialog;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.app.Fragment;
import android.util.DisplayMetrics;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;


public class FragmentImageView extends Fragment {
 
    private Integer itemData;
    private String path;
    private Bitmap myBitmap;
    public ProgressDialog pd;
    private ImageView ivImage;
 
    public static FragmentImageView newInstance() {
        FragmentImageView f = new FragmentImageView();
        return f;
    }
 
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }
    
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.imageview, container, false);
        ivImage = (ImageView) root.findViewById(R.id.ivImageView);
        setImageInViewPager();
        return root;
    }
    
    //public void setImageList(Integer integer) {
    //public void setImageList(String path) {
    //public void setImageList(Bitmap image) {
    public void setImageList(String path) {
        //this.itemData = integer;    	
    	//this.inputPath = path;
    	//this.myBitmap = image;
    	this.path = path;
    }
    
    public void setImageInViewPager() {
        try {
            //if image size is too large. Need to scale as below code.
 
        	//String inputPath = Environment.getExternalStorageDirectory() + "/enact_input/Icet.bmp";
            BitmapFactory.Options options = new BitmapFactory.Options();
            options.inJustDecodeBounds = true;
            options.inMutable = true;
            //myBitmap = BitmapFactory.decodeResource(getResources(), itemData, options);
            myBitmap = BitmapFactory.decodeFile(path, options);
            if (options.outWidth > 3000 || options.outHeight > 2000) {
                options.inSampleSize = 3;
            } else if (options.outWidth > 2000 || options.outHeight > 1500) {
                options.inSampleSize = 2;
            } else if (options.outWidth > 1000 || options.outHeight > 1000) {
                options.inSampleSize = 1;
            }
            
//            DisplayMetrics metrics = this.getResources().getDisplayMetrics();
//            int width = metrics.widthPixels;
//            int height = metrics.heightPixels;
//            
//            myBitmap = Bitmap.createScaledBitmap(myBitmap, width, height, false);
            options.inJustDecodeBounds = false;
            //myBitmap = BitmapFactory.decodeResource(getResources(), itemData, options);
            myBitmap = BitmapFactory.decodeFile(path, options);
            if (myBitmap != null) {
                try {
                    if (ivImage != null) {
                        ivImage.setImageBitmap(myBitmap);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        } catch (OutOfMemoryError e) {
            e.printStackTrace();
            System.gc();
        }
    }
 
    @Override
    public void onDestroyView() {
        super.onDestroyView();
        if (myBitmap != null) {
            myBitmap.recycle();
            myBitmap = null;
        }
    }
}
//- See more at: http://www.theappguruz.com/blog/android-image-fragment-pager-view/#sthash.2QCoGC9v.dpuf