package chanct;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.NavigableMap;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.Cell;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.KeyValue;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.Admin;
import org.apache.hadoop.hbase.client.Connection;
import org.apache.hadoop.hbase.client.ConnectionFactory;
import org.apache.hadoop.hbase.client.Delete;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.ResultScanner;
import org.apache.hadoop.hbase.client.Row;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.client.Table;
import org.apache.hadoop.hbase.exceptions.DeserializationException;
import org.apache.hadoop.hbase.filter.Filter;
import org.apache.hadoop.hbase.filter.SingleColumnValueFilter;
import org.apache.hadoop.hbase.filter.CompareFilter.CompareOp;
import org.apache.hadoop.hbase.util.Bytes;

public class HBase {
	// 与HBase数据库的连接对象
    Connection connection;
    Configuration conf;
    // 数据库元数据操作对象
    Admin admin;
    public HBase(){
    	connection = null;
    	conf = null;
    	admin = null;
    }
    protected void destroy() throws IOException{
    	System.out.println("into finalize");
        if(null != admin){
        	admin.close();
        }
        if (null != connection){
        	connection.close();
        }
    }
    protected void finalize() throws Throwable {  
        destroy();
        super.finalize();
    }
    
    public Boolean setup(String zk_addr){
    	Boolean b_success = true;
    	conf = HBaseConfiguration.create();
    	// 设置连接参数：HBase数据库所在的主机IP
        conf.set("hbase.zookeeper.quorum", zk_addr);
        // 设置连接参数：HBase数据库使用的端口
        conf.set("hbase.zookeeper.property.clientPort", "2181");

        try {
            // 取得一个数据库连接对象
        	connection = ConnectionFactory.createConnection(conf);
            // 取得一个数据库元数据操作对象
        	admin = connection.getAdmin();
		} catch (IOException e) {
			b_success = false;
		}
        return b_success;
    }
    
    /**
     * 创建表，cf为列族列表
     */
	public Boolean createTable(String tablename, ArrayList<String> cflist) throws IOException {
		
		Boolean b_success = true;
		TableName tableName = TableName.valueOf(tablename);
		if(admin.tableExists(tableName)){
			b_success = false;
		}else{
			// 数据表描述对象
            HTableDescriptor hTableDescriptor = new HTableDescriptor(tableName);
            Iterator<String> it = cflist.iterator();
            while (it.hasNext()){
            	String obj = it.next();
            	// 列族描述对象
                HColumnDescriptor family= new HColumnDescriptor(obj);
                // 在数据表中新建一个列族
                hTableDescriptor.addFamily(family);
            }

            // 新建数据表
            admin.createTable(hTableDescriptor);
		}
		return b_success;
	}
	/**
	 * 获取表的控制句柄
	 * @param tableName
	 * @return not null if gettable success.
	 * @throws IOException
	 * @desc: 使用结束后使用table.close() 将连接关闭.
	 */
	public Table getTable(String tablename) throws IOException{
		TableName tableName = TableName.valueOf(tablename);
		Table table = null;
		if(admin.tableExists(tableName)){
			table = connection.getTable(tableName);
		}
		
		return table;
	}
	/**
	 * 清空表
	 */
	public void truncateTable(String tablename) throws IOException{
        // 取得目标数据表的表名对象
        TableName tableName = TableName.valueOf(tablename);

        // 设置表状态为无效
        admin.disableTable(tableName);
        // 清空指定表的数据
        admin.truncateTable(tableName, true);
    }

    /**
     * 删除表
     */
    public void deleteTable(String tablename) throws IOException{
        // 设置表状态为无效
        admin.disableTable(TableName.valueOf(tablename));
        // 删除指定的数据表
        admin.deleteTable(TableName.valueOf(tablename));
    }
    
    /**
     * 增加一条数据
     */
    public Boolean putData(String tablename, String rowkey, String cf, String col, byte[] value){
    	Boolean b_success = true;
    	try {
			Table table = connection.getTable(TableName.valueOf(tablename));
			Put put = new Put(Bytes.toBytes(rowkey));
			put.addColumn(Bytes.toBytes(cf), Bytes.toBytes(col), value);
			table.put(put);
			table.close();
		} catch (IOException e) {
			b_success = false;
		}
    	
    	return b_success;
    }
    
    public Boolean putData(Table table, String rowkey, String cf, String col, byte[] value){
    	Boolean b_success = true;
    	try {
			Put put = new Put(Bytes.toBytes(rowkey));
			put.addColumn(Bytes.toBytes(cf), Bytes.toBytes(col), value);
			table.put(put);
		} catch (IOException e) {
			b_success = false;
		}
    	
    	return b_success;
    }
    
    /**
     * 获取一列数据
     */
    public byte[] getData(String tablename, String rowkey, String cf, String col){
    	byte[] val = new byte[0];
    	try {
			Table table = connection.getTable(TableName.valueOf(tablename));
			Get get = new Get(Bytes.toBytes(rowkey));
			get.addColumn(Bytes.toBytes(cf), Bytes.toBytes(col));
			Result result = table.get(get);
			for(KeyValue kv: result.list()){
				val = kv.getValue();
				System.out.println("key:"+kv + " val:"+Bytes.toString(val));
			}
			table.close();
		} catch (IOException e) {
			
		}
    	return val;
    }
    public byte[] getData(Table table, String rowkey, String cf, String col){
    	byte[] val = null;
    	try {
			Get get = new Get(Bytes.toBytes(rowkey));
			get.addColumn(Bytes.toBytes(cf), Bytes.toBytes(col));
			Result result = table.get(get);
			for(KeyValue kv: result.list()){
				val = kv.getValue();
				System.out.println("key:"+kv + " val:"+Bytes.toString(val));
			}
			table.close();
		} catch (IOException e) {
			
		}
    	return val;
    }
    /**
     * 获取一行数据
     * 返回值为{"col1":"val", "col2":"val"}形式的map
     */
    public NavigableMap<byte[],byte[]> getCfData(String tablename, String rowkey, String cf){
    	
    	NavigableMap<byte[],byte[]>quaMap = null;
    	try {
			Table table = connection.getTable(TableName.valueOf(tablename));
			Get get = new Get(Bytes.toBytes(rowkey));
			get.addFamily(cf.getBytes());
			Result result = table.get(get);
			quaMap =  result.getFamilyMap(cf.getBytes());
			for(byte[] quaByte : quaMap.keySet()){  
				
                byte[] valueByte = quaMap.get(quaByte);
                String quaName = Bytes.toString(quaByte);
                String value = Bytes.toString(valueByte);
                System.out.println("col:" + quaName + " val:"+value);
            }
			table.close();
		} catch (IOException e) {
			
		}
    	return quaMap;
    }
    public NavigableMap<byte[],byte[]> getCfData(Table table, String rowkey, String cf){
    	
    	NavigableMap<byte[],byte[]>quaMap = null;
    	try {
			Get get = new Get(Bytes.toBytes(rowkey));
			get.addFamily(cf.getBytes());
			Result result = table.get(get);
			quaMap =  result.getFamilyMap(cf.getBytes());
			for(byte[] quaByte : quaMap.keySet()){  
				
                byte[] valueByte = quaMap.get(quaByte);
                String quaName = Bytes.toString(quaByte);
                String value = Bytes.toString(valueByte);
                System.out.println("col:" + quaName + " val:"+value);
            }
		} catch (IOException e) {
			
		}
    	return quaMap;
    }
    
    public void deleteRow(String tablename, String rowKey) throws IOException{
    	Table table = connection.getTable(TableName.valueOf(tablename));
    	Delete delete = new Delete(Bytes.toBytes(rowKey));
    	table.delete(delete);
    }
    public void deleteRow(Table table, String rowKey) throws IOException{
    	Delete delete = new Delete(Bytes.toBytes(rowKey));
    	table.delete(delete);
    }
    
    public static void main(String[] args) throws IOException {
    	HBase hbase = new HBase();
    	hbase.setup("172.26.3.23");
    	String tableName = "hbasefile";
    	String cf = "fileinfo";
    	ArrayList<String> cf_list = new ArrayList<String>();
    	cf_list.add(cf);
    	hbase.createTable(tableName,cf_list);
    	
    	hbase.putData(tableName,"file1", cf, "name", "file1".getBytes());
    	hbase.putData(tableName,"file1", cf, "name", "newfile".getBytes());
    	hbase.putData(tableName,"file1", cf, "size", "10".getBytes());
    	hbase.putData(tableName,"file2", cf, "name", "file2".getBytes());
    	byte[] val = hbase.getData(tableName, "file1", cf, "name");
    	System.out.println("getdata:" + Bytes.toString(val));
    	
    	
    	hbase.truncateTable(tableName);
    	hbase.deleteTable(tableName);
    	System.out.println("Finished...");
    }
}