package hbaseFS;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

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
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.client.Table;
import org.apache.hadoop.hbase.exceptions.DeserializationException;
import org.apache.hadoop.hbase.filter.Filter;
import org.apache.hadoop.hbase.filter.SingleColumnValueFilter;
import org.apache.hadoop.hbase.filter.CompareFilter.CompareOp;
import org.apache.hadoop.hbase.util.Bytes;

public class hbaseOP {
	// 与HBase数据库的连接对象
    static Connection connection;

    // 数据库元数据操作对象
    static Admin admin;
    
    public static Boolean setup(String zk_ip, String zk_port){
    	Boolean b_success = true;
    	Configuration conf = HBaseConfiguration.create();
    	// 设置连接参数：HBase数据库所在的主机IP
        conf.set("hbase.zookeeper.quorum", "192.168.137.13");
        // 设置连接参数：HBase数据库使用的端口
        conf.set("hbase.zookeeper.property.clientPort", "2181");

        try {
            // 取得一个数据库连接对象
        	connection = ConnectionFactory.createConnection(conf);
            // 取得一个数据库元数据操作对象
        	admin = connection.getAdmin();
		} catch (IOException e) {
			b_success = false;
			e.printStackTrace();
		}
        return b_success;
    }
    
    /**
     * 创建表，cf为列族列表
     */
	public static Boolean create_table(String table, ArrayList<String> cflist) throws IOException {
		Boolean b_success = true;
		TableName tableName = TableName.valueOf(table);
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
	 * 清空表
	 */
	public void truncateTable(String table) throws IOException{
        // 取得目标数据表的表名对象
        TableName tableName = TableName.valueOf(table);

        // 设置表状态为无效
        admin.disableTable(tableName);
        // 清空指定表的数据
        admin.truncateTable(tableName, true);
        // 设置表状态为有效
        admin.enableTable(tableName);
    }

    /**
     * 删除表
     */
    public void deleteTable(String table) throws IOException{
        // 设置表状态为无效
        admin.disableTable(TableName.valueOf(table));
        // 删除指定的数据表
        admin.deleteTable(TableName.valueOf(table));
    }
    
    /**
     * 增加一条数据
     */
    public Boolean putData(String tableName, String rowkey, String cf, String col, byte[] value){
    	Boolean b_success = true;
    	try {
			Table table = connection.getTable(TableName.valueOf(tableName));
			Put put = new Put(Bytes.toBytes(rowkey));
			put.addColumn(Bytes.toBytes(cf), Bytes.toBytes(col), value);
			table.put(put);
			table.close();
		} catch (IOException e) {
			b_success = false;
		}
    	
    	return b_success;
    }
    
    /**
     * 获取一列数据
     */
    public String getData(String tableName, String rowkey, String cf, String col){
    	String val = "";
    	try {
			Table table = connection.getTable(TableName.valueOf(tableName));
			Get get = new Get(Bytes.toBytes(rowkey));
			get.addColumn(Bytes.toBytes(cf), Bytes.toBytes(col));
			Result result = table.get(get);
			for(KeyValue kv: result.list()){
				val = Bytes.toString(kv.getValue());
			}
			table.close();
		} catch (IOException e) {
			
		}
    	return val;
    }

}
