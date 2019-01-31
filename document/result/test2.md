#test2

##1.0      构造函数      

###鍑芥暟:     __construct(Connection $connection = null, $model = null)    

	璇存槑:

	* @access  public
   
	* @param  Connection  $connection  数据库对象实例

##1.1      利用__call方法实现一些特殊的Model方法      

###鍑芥暟:     __call($method, $args)    

	璇存槑:

	* @access  public
   
	* @param  string  $method  方法名称

	* @param  array  $args  调用参数

	* @return  mixed
   
	* @throws  DbException
   
##1.2      获取当前的数据库Connection对象      

###鍑芥暟:     getConnection()    

	璇存槑:

	* @access  public
   
##1.3      切换当前的数据库连接      

###鍑芥暟:     connect($config)    

	璇存槑:

	* @access  public
   
	* @param  mixed  $config
  
##1.4      设置当前的数据库Builder对象      

###鍑芥暟:     protected setBuilder()    

	璇存槑:

	* @access  protected
   
##1.5      获取当前的模型对象实例      

###鍑芥暟:     getModel()    

	璇存槑:

	* @access  public
   
##1.6      设置后续从主库读取数据      

###鍑芥暟:     readMaster($allTable = false)    

	璇存槑:

	* @access  public
   
	* @param  bool  $allTable
  
##1.7      获取当前的builder实例对象      

###鍑芥暟:     getBuilder()    

	璇存槑:

	* @access  public
   
##1.8      指定默认的数据表名（不含前缀）      

###鍑芥暟:     name($name)    

	璇存槑:

	* @access  public
   
	* @param  string  $name
  
##1.9      指定默认数据表名（含前缀）      

###鍑芥暟:     setTable($table)    

	璇存槑:

	* @access  public
   
	* @param  string  $table  表名

##1.10      得到当前或者指定名称的数据表      

###鍑芥暟:     getTable($name = '')    

	璇存槑:

	* @access  public
   
	* @param  string  $name
  
##1.11      将SQL语句中的__TABLE_NAME__字符串替换成带前缀的表名（小写）      

###鍑芥暟:     parseSqlTable($sql)    

	璇存槑:

	* @access  public
   
	* @param  string  $sql  sql语句

##1.12      执行查询 返回数据集      

###鍑芥暟:     query($sql, $bind = [], $master = false, $class = false)    

	璇存槑:

	* @access  public
   
	* @param  string  $sql  sql指令

	* @param  array  $bind  参数绑定

	* @param  boolean  $master  是否在主服务器读操作

	* @param  bool|string  $class  指定返回的数据集对象

	* @return  mixed
   
	* @throws  BindParamException
   
##1.13      执行语句      

###鍑芥暟:     execute($sql, $bind = [])    

	璇存槑:

	* @access  public
   
	* @param  string  $sql  sql指令

	* @param  array  $bind  参数绑定

	* @return  int
   
	* @throws  BindParamException
   
##1.14      获取最近插入的ID      

###鍑芥暟:     getLastInsID($sequence = null)    

	璇存槑:

	* @access  public
   
	* @param  string  $sequence  自增序列名

##1.15      获取最近一次查询的sql语句      

###鍑芥暟:     getLastSql()    

	璇存槑:

	* @access  public
   
##1.16      执行数据库事务      

###鍑芥暟:     transaction($callback)    

	璇存槑:

	* @access  public
   
	* @param  callable  $callback  数据操作方法回调

##1.17      启动事务      

###鍑芥暟:     startTrans()    

	璇存槑:

	* @access  public
   
##1.18      用于非自动提交状态下面的查询提交      

###鍑芥暟:     commit()    

	璇存槑:

	* @access  public
   
	* @return  void
   
##1.19      事务回滚      

###鍑芥暟:     rollback()    

	璇存槑:

	* @access  public
   
	* @return  void
   
##1.20      批处理执行SQL语句      批处理的指令都认为是execute操作      

###鍑芥暟:     batchQuery($sql = [], $bind = [])    

	璇存槑:

	* @access  public
   
	* @param  array  $sql  SQL批处理指令

##1.21      获取数据库的配置参数      

###鍑芥暟:     getConfig($name = '')    

	璇存槑:

	* @access  public
   
	* @param  string  $name  参数名称

##1.22      得到分表的的数据表名      

###鍑芥暟:     getPartitionTableName($data, $field, $rule = [])    

	璇存槑:

	* @access  public
   
	* @param  array  $data  操作的数据

	* @param  string  $field  分表依据的字段

	* @param  array  $rule  分表规则


