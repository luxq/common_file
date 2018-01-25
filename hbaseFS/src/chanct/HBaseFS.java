package chanct;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Iterator;
import chanct.HBase;

import org.apache.hadoop.hbase.client.Table;
import org.apache.hadoop.hbase.util.Bytes;

public class HBaseFS {
	private HBase hbase;
    private Boolean b_init;
    private String table_name;
    private Table table;
    
    public HBaseFS(){
    	hbase = new HBase();
    	b_init = false;
    	table_name = "";
    	table = null;
    }
    
    protected void destroy() throws IOException{
    	if(null != table){
    		table.close();
    	}
    }
    protected void finalize() throws java.lang.Throwable {
    	destroy();
    	super.finalize();
    }
    
    public Boolean init(String zk_host, String tablename) throws IOException{
    	Boolean b_success = false;
    	table_name = tablename;
    	if(hbase.setup(zk_host)){
    		table = hbase.getTable(tablename);
    		b_success = (table!=null) ? true : false;
    	}
        
    	b_init = b_success;
        return b_success;
    }
    
    public void saveFile(String path) throws IOException{
    	if(!b_init)
    		return;
    	
    	File file = new File(path);
    	String filename = "";
    	String parentdir = "";
    	long filesize = 0;
    	byte[] con = null;
    	if(file.exists()){
    		if(file.isFile()){
        		filename = getFileName(path);
        		parentdir= getFileDir(path);
        		filesize = getFileSize(path);
        		con = getFileContent(path);
        		hbase.putData(table, filename, "fileinfo", "name", filename.getBytes());
        		hbase.putData(table, filename, "fileinfo", "parent", parentdir.getBytes());
        		hbase.putData(table, filename, "fileinfo", "size", Long.toString(filesize).getBytes());
        		hbase.putData(table, filename, "fileinfo", "content", con);
        		System.out.println("saveFile:"+path);
    		}else{
    			ArrayList<String> flist = getFileList(path,0);
    			Iterator<String> it = flist.iterator();
    	        while (it.hasNext()){
    	        	String filepath = it.next();
    	        	filename = getFileName(filepath);
            		parentdir= getFileDir(filepath);
            		filesize = getFileSize(filepath);
            		con = getFileContent(filepath);
            		hbase.putData(table, filename, "fileinfo", "name", filename.getBytes());
            		hbase.putData(table, filename, "fileinfo", "parent", parentdir.getBytes());
            		hbase.putData(table, filename, "fileinfo", "size", Long.toString(filesize).getBytes());
            		hbase.putData(table, filename, "fileinfo", "content", con);
            		System.out.println("saveFile:"+filepath);
    	        }
    		}
    	}
    }
    
    public byte[] getFile(String filename) throws IOException{
    	byte[] content = null;
    	if(b_init){
    		content = hbase.getData(table, filename, "fileinfo", "content");
    	}
    	return content;
    }
    
    public void deleteFile(String filename) throws IOException{
    	if(b_init){
    		hbase.deleteRow(table, filename);
    	}
    }

	


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
            if(array[i].isFile() && (array[i].length() < 10*1024*1024))//如果是文件
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
	private static byte[] getFileContent(String filepath) throws IOException{
	    	
	    File file = new File(filepath);
	    
	    byte buffer[] = new byte[(int) file.length()]; // 缓冲区字节数组
	    if(file.length() == 0)
	    	return buffer;
	    
	    InputStream fis = new FileInputStream(file);
	    BufferedInputStream bis = new BufferedInputStream(fis, (int)file.length());
	
       	int readSize = -1; // 记录每次实际读取字节数
		if (null != bis && (readSize = bis.read(buffer)) != -1)
		{
		   
		}
		
		bis.close();
	    
	    return buffer;
	}
	private static long getFileSize(String filepath) {
    	
	    File file = new File(filepath);
	    return file.length();
	}
	private static String getFileName(String filepath) {
    	
	    File file = new File(filepath);
	    return file.getName();
	}
	private static String getFileDir(String filepath) {
    	
	    File file = new File(filepath);
	    return file.getParent();
	}
    
	public static void main(String[] args) throws IOException {   
        //这是需要获取的文件夹路径  
        String path = "/root/";
        String getFilename = "spark_start.sh";
        String savePath = "/mnt/code/spark_start.sh";
        String tablename = "hbasefile";
        HBase hbase = new HBase();
        hbase.setup("172.26.3.29");
        ArrayList<String> cflist = new ArrayList<String>();
        cflist.add("fileinfo");
        hbase.createTable(tablename, cflist);       	
        		
        HBaseFS hfs = new HBaseFS();
        hfs.init("172.26.3.29", tablename);
        // 保存文件
        hfs.saveFile(path);
        
        // 获取并保存文件
        byte[] con = hfs.getFile(getFilename);
        if (con != null){
        	OutputStream fos = new FileOutputStream(savePath);
        	BufferedOutputStream bos = new BufferedOutputStream(fos, con.length);
        	bos.write(con, 0, con.length);
        	bos.flush();
        	bos.close();
        }
        
        // 删除文件
        hfs.deleteFile(getFilename);
        
        System.out.println("Test finished...");
        /*
        ArrayList<String> flist = getFileList(path,0);
        Iterator<String> it = flist.iterator();
        while (it.hasNext()){
        	String parentdir = "";
        	long   file_size = 0;
        	String filename = "";
        	String filepath = it.next();
        	file_size = getFileSize(filepath);
        	filename = getFileName(filepath);
        	parentdir = getFileDir(filepath);
        	byte[] con = new byte[0];
        	if(file_size < 1024*1024*5)// 5MB
        	{
        		con = getFileContent(filepath);
        	}
        	System.out.println("**********************  Start **************");
        	System.out.println("FilePath:"+ filepath);
        	System.out.println("FileSize:"+ file_size);
        	System.out.println("FileName:"+ filename);
        	System.out.println("FileDir:"+ parentdir);
        	System.out.println("FileContentlen:"+ con.length);
        	System.out.println("**********************  End **************");
        	
        }
        */
    }
} 
