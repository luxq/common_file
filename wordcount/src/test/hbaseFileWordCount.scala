package test

import org.apache.spark.sql.SparkSession
//import org.apache.spark.SparkContext
import org.apache.hadoop.hbase.HBaseConfiguration
import org.apache.hadoop.hbase.HTableDescriptor
import org.apache.hadoop.hbase.client.HBaseAdmin
import org.apache.hadoop.hbase.client.Put
import org.apache.hadoop.hbase.client.HTable
import org.apache.hadoop.hbase.client.Result

import org.apache.hadoop.hbase.mapreduce.TableInputFormat
import org.apache.hadoop.hbase.HColumnDescriptor
import org.apache.hadoop.hbase.util.Bytes
import org.apache.hadoop.hbase.io.ImmutableBytesWritable 
import org.apache.hadoop.hbase.client.Delete 
object hbaseFileWordCount {
    def main(args: Array[String]) {
        val spark = SparkSession.builder.appName("HbaseFileWordCount").getOrCreate()
        val sc = spark.sparkContext
        
        val tablename = "file_table"
        val conf = HBaseConfiguration.create()    
        conf.set("hbase.zookeeper.property.clientPort", "2181")  
        conf.set("hbase.zookeeper.quorum", "127.0.0.1")  
        //conf.set("hbase.master", "127.0.0.1:60000")   
        //conf.addResource("/usr/local/hbase/conf/hbase-site.xml")    
        conf.set(TableInputFormat.INPUT_TABLE, tablename)    
      
        val admin = new HBaseAdmin(conf)    
        if (!admin.isTableAvailable(tablename)) {    
          println("Table Not Exists! Exit!")
          return
        }    
        
        //Scan操作  
        val hbaseRDD = sc.newAPIHadoopRDD(conf, classOf[TableInputFormat],    
            classOf[org.apache.hadoop.hbase.io.ImmutableBytesWritable],    
            classOf[org.apache.hadoop.hbase.client.Result])    
        
        hbaseRDD.cache()    
        val file_map = hbaseRDD.map{case (_,result) =>{  
            //获取行键  
            val key = Bytes.toString(result.getRow)  
            //通过列族和列名获取文件内容  
            val lines = Bytes.toString(result.getValue("fileinfo".getBytes,"file_content".getBytes)).split("\n")
            val wordcount = lines.map(line => line.split(" ").filter(_.nonEmpty).length).reduce(_+_)
            (key,wordcount)
        }}
        
        file_map.foreach(println)
        System.exit(0)    
    } 
}