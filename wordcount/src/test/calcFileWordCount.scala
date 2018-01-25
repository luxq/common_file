package test
import org.apache.spark.SparkConf
import org.apache.spark.SparkContext
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

object calcFileWordCount extends Serializable {
  def main(args: Array[String]) {
    val sconf = new SparkConf()
    val sc = new SparkContext(sconf)    
    val config = new HBaseConfiguration()
    val tablename = "filetable"
    
    val conf = HBaseConfiguration.create()    
    conf.set("hbase.zookeeper.property.clientPort", "2181")  
    conf.set("hbase.zookeeper.quorum", "127.0.0.1")  
    conf.set("hbase.master", "127.0.0.1:60000")   
    conf.addResource("/usr/local/hbase/conf/hbase-site.xml")    
    conf.set(TableInputFormat.INPUT_TABLE, tablename)    
    
    val admin = new HBaseAdmin(conf)    
    if (!admin.isTableAvailable(tablename)) {
        print("Table Not Exists! Program exit !!!")
        return
    }    
    
    //Scan操作  
    val hbaseRDD = sc.newAPIHadoopRDD(conf, classOf[TableInputFormat],    
      classOf[org.apache.hadoop.hbase.io.ImmutableBytesWritable],    
      classOf[org.apache.hadoop.hbase.client.Result])    
    
    val count = hbaseRDD.count()    
    println("HBase RDD Count:" + count)    
    hbaseRDD.cache()    
    /*
    val res = hbaseRDD.take(count.toInt)    
    for (j <- 1 until count.toInt) {    
      println("j: " + j)    
      var rs = res(j - 1)._2    
      var kvs = rs.raw    
      for (kv <- kvs)    
        println("rowkey:" + new String(kv.getRow()) +    
          " cf:" + new String(kv.getFamily()) +    
          " column:" + new String(kv.getQualifier()) +    
          " value:" + new String(kv.getValue()))    
    } 
    * 
    */
//    val filecontent = hbaseRDD.map(m => m._2.listCells()).map( c => 

    val sqlContext = new org.apache.spark.sql.SQLContext(sc)
    val schema = sqlContext.createDataFrame(filecontent)
    hbaseRDD.foreach{case (_,result) =>{  
      //获取行键  
      val key = Bytes.toString(result.getRow)  
      //通过列族和列名获取列  
      val m_val = Bytes.toString(result.getValue("basic".getBytes,"name".getBytes))  
      println("Row key:"+key+" value:"+m_val)  
    }}  
    
    System.exit(0)    
  } 
}
