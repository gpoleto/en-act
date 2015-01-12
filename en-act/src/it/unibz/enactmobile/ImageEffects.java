package it.unibz.enactmobile;

import java.io.FileOutputStream;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Color;
import android.util.Log;

public class ImageEffects {
	
	private final static String TAG = "ImageEfects";

	public static String effectGrayscale(String inputPath, String outputPath){
		
//		BufferedImage image = ImageIO.read(new File(inputPath));
//		BufferedImage image = ImageIO.read(
//		         new URL("http://upload.wikimedia.org/wikipedia/en/2/24/Lenna.png"));
		
		BitmapFactory.Options opts = new BitmapFactory.Options();
		opts.inMutable = true;
		Bitmap image = BitmapFactory.decodeFile(inputPath, opts);
		
		int width = image.getWidth();
		int height = image.getHeight();
		
		int[] data = new int[width*height];
		image.getPixels(data, 0, width, 0, 0, width, height);
		
		//Try to make picture RED to check if the pixels are read correctly.
//		int col = image.getPixel(0, height-1);
//		int col = image.getPixel(304,306);
//		Log.v(TAG, "First (C++) pixel col / RGB values: (col): " + col + " / [R]: " + Color.red(col) + " / [G]: " + Color.green(col) + " / [B]: " + Color.blue(col) + " / [A]: " + Color.alpha(col));
//		
//		int rounding_r = (int)Math.round(Color.red(col) * 0.2126);
//		int rounding_g = (int)Math.round(Color.green(col) * 0.7152);
//		int rounding_b = (int)Math.round(Color.blue(col) * 0.0722);
//		Log.v(TAG, "Rounding: " + rounding_r + " + " + rounding_g + " + " + rounding_b);
//		
//		int gray = ( (int)Math.round(Color.red(col) * 0.2126) ) + ((int)Math.round(Color.green(col) * 0.7152)) + ((int)Math.round(Color.blue(col) * 0.0722)); 
//		Log.v(TAG, "Rounding the whole: " + gray);
		
		for (int r=0; r<height; r++) {
			for (int c=0; c<width; c++) {
				//grayscale here
				int color = image.getPixel(c,r);
				int grayscale = ( (int)Math.round(Color.red(color) * 0.2126) ) + ((int)Math.round(Color.green(color) * 0.7152)) + ((int)Math.round(Color.blue(color) * 0.0722)); 
				
				//int grayscale = (floor(data[i+2] * 0.2126 + 0.5)) + (floor(data[i+1] * 0.7152 + 0.5)) + floor(data[i] * 0.0722 + 0.5);

//				data[i] = grayscale;
//				data[i+1] = grayscale;
//				data[i+2] = grayscale;
				
				
				//image.setPixel(c, r, Color.argb(Color.alpha(color), grayscale, grayscale, grayscale));
				image.setPixel(c, r, Color.rgb(grayscale, grayscale, grayscale));
			}
		}
		
		String[] pieces = inputPath.split("\\.");
		Log.v(TAG, "TYPE: " + pieces[pieces.length-1]);
		Log.v(TAG, "TYPE: " + pieces[0]);
		
//		int coll = image.getPixel(304,306);
//		Log.v(TAG, "First (C++) pixel RGB values after effect: [R]: " + Color.red(coll) + " / [G]: " + Color.green(coll) + " / [B]: " + Color.blue(coll));
		
		outputPath += "/image_result_Java";
		FileOutputStream out = null;
		try {
//		       out = new FileOutputStream(outputPath);
		       if(pieces[pieces.length-1].equals("jpg") || 
		    		   pieces[pieces.length-1].equals("JPG") || 
		    		   pieces[pieces.length-1].equals("jpeg") || 
		    		   pieces[pieces.length-1].equals("JPEG") || 
		    		   pieces[pieces.length-1].equals("jpe") || 
		    		   pieces[pieces.length-1].equals("JPE") ) {
		    	   
		    	   out = new FileOutputStream(outputPath+".jpg");
		    	   outputPath += ".jpg";
		    	   image.compress(Bitmap.CompressFormat.JPEG, 100, out);
		       }
		    	   
		       else {
		    	   out = new FileOutputStream(outputPath+".png");
		    	   outputPath += ".png";
		    	   image.compress(Bitmap.CompressFormat.PNG, 100, out);
		       }
		    	  
		} catch (Exception e) {
		    e.printStackTrace();
		} finally {
		       try{
		           out.close();
		       } catch(Throwable ignore) {}
		}
		
//		ImageIO.write(image, "png", new File(outputPath));
//		int t = BYTE_PER_PIXEL;
		
		
		
		
		
		
		
//		FileInputStream fis = null;
//		File image = new File(inputPath);
//		try {
//			fis = new FileInputStream(image);
//		
//		
//			byte[] data = new byte[(int) image.length()];
//			Log.v(TAG, "image.length(): " + String.valueOf((int) image.length()));
//			
//			int size = fis.read(data);
//			Log.v(TAG, "size = " + String.valueOf(size));
//			
////			int width = data[18] * 256 + data[19];
////			int height = getIntFromByte(data, 22, 23);
//			
//			byte[] w = new byte[4];
//			byte[] h = new byte[4];
//			
//			for (int i = 0; i<w.length; i++) {
//				w[i] = data[18+i];
//			}
//			
//			for (int i = 0; i<h.length; i++) {
//				h[i] = data[22+i];
//			}
//			
//			//Log.v(TAG, "width = " + width + " / height = " + height);
//			Log.v(TAG, "data[18] = " + new Byte(data[18]).longValue() + " / data[19] = " + new Byte(data[19]).longValue());
//			ByteBuffer wrapped_w = ByteBuffer.wrap(w);
//			ByteBuffer wrapped_h = ByteBuffer.wrap(h);
//			
//			int width = (int) wrapped_w.getInt();
//			int height = (int) wrapped_h.getInt();
//			Log.v(TAG, "width = " + width + " / height = " + height);
//			
//			int nw = 477;
//			int nh = 356;
//			byte[] nwb = ByteBuffer.allocate(4).putInt(nw).array();
//			byte[] nhb = ByteBuffer.allocate(4).putInt(nh).array();
//			String indices = "";
//			ByteBuffer data_wrapped = ByteBuffer.wrap(data);
//			for (int i = 0; i<data.length-3; i++) {
//				int t = BMP_OFFSET_IMAGE_DATA_BYTES;
//				int ww = (int)data_wrapped.getShort(i);
//				if(ww == 356 || ww == 477/* || ww == -356 || ww == -477*/)
//					indices += i + "~";
//				//int hh = (int)data_wrapped.getInt(22);
////				if(nwb[1] == data[i])
////					if(nwb[2] == data[i+1])
////						if(nwb[3] == data[i+2])
////							if(nwb[4] == data[i+3]) {
////								indices += i + "~";
////							}
//			}
//			Log.v(TAG, "indices where the width is stored: " + indices);
//			Log.v(TAG, "First RGB values: [R]: " + (int)data[56] + " / [G]: " + (int)data[55] + " / [B]: " + (int)data[54]);
//			
//			
//			//Log.v(TAG, "ww = " + ww + " / hh = " + hh);
//			//try {
//			fis.close();
//		} catch (Exception e) { e.printStackTrace(); }
		//return "image Java";
		return outputPath;
	}
	
	private static int getIntFromByte(byte[] bytes, int start, int end) {
		int value = 0;
		
		for (int i = start; i < end; i++) {
			value += bytes[i] << 8 | bytes[i+1];
			//value += 
			
		}
		
		return value;
	}
	
}
