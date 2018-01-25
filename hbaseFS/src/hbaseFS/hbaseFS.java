package hbaseFS;
import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Iterator;


public class hbaseFS {
	public static void main(String[] args) {   
        //这是需要获取的文件夹路径  
        String path = "/root/";   
        ArrayList<String> flist = getFileList(path,0);
        Iterator<String> it = flist.iterator();
        while (it.hasNext()){
        	Object obj = it.next();
        	System.out.println("File:"+obj);
        }
    }

    /*
     * 函数名：getFile
     * 作用：使用递归，输出指定文件夹内的所有文件
     * 参数：path：文件夹路径   deep：表示文件的层次深度，控制前置空格的个数
     * 前置空格缩进，显示文件层次结构
     */
    private static ArrayList<String> getFileList(String path,int deep){   
        // 获得指定文件对象  
    	ArrayList<String> flist = new ArrayList<String>();
        File file = new File(path);
        if(file.isFile())
        {
        	flist.add(path);
        	return flist;
        }
        if(deep > 2)
        {
        	return flist;
        }
        // 获得该文件夹内的所有文件   
        File[] array = file.listFiles();   
        for(int i=0; i<array.length; i++)
        {   
            if(array[i].isFile())//如果是文件
            {
            	flist.add(array[i].getPath());
            }
            else if(array[i].isDirectory())//如果是文件夹
            {  
                //flist.addAll(getFileList(array[i].getPath(),deep+1));  
            }   
        }   
        return flist;
    }
    public static byte[] getFileContent(String filepath) throws IOException{
	    	
	    File file = new File(filepath);
	    byte buffer[] = new byte[(int) file.length()]; // 缓冲区字节数组
	    
	    InputStream fis = new FileInputStream(file);
	    BufferedInputStream bis = new BufferedInputStream(fis, (int)file.length());
	
	    try {
	    	int readSize = -1; // 记录每次实际读取字节数
			if (null != bis && (readSize = bis.read(buffer)) != -1)
			{
			   
			}
		}finally{
			bis.close();
		}
	    
	    return buffer;
	}
    public static long getFileSize(String filepath) {
    	
	    File file = new File(filepath);
	    return file.length();
	}
    public static String getFileName(String filepath) {
    	
	    File file = new File(filepath);
	    return file.getName();
	}
    public static String getFileDir(String filepath) {
    	
	    File file = new File(filepath);
	    return file.getParent();
	}
    
} 

