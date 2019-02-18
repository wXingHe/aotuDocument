# 3 test2

## 3.1      构造函数      

### 函数:     __construct(Connection $connection = null, $model = null)    

	说明:

	*  @access  public
   
	*  @param  Connection  $connection  数据库对象实例

## 3.2      利用__call方法实现一些特殊的Model方法      

### 函数:     __call($method, $args)    

	说明:

	*  @access  public
   
	*  @param  string  $method  方法名称

	*  @param  array  $args  调用参数

	*  @return  mixed
   
	*  @throws  DbException
   
## 3.3      获取当前的数据库Connection对象      

### 函数:     getConnection()    

	说明:

	*  @access  public
   
## 3.4      切换当前的数据库连接      

### 函数:     connect($config)    

	说明:

	*  @access  public
   
	*  @param  mixed  $config
  
## 3.5      设置当前的数据库Builder对象      

### 函数:     protected setBuilder()    

	说明:

	*  @access  protected
   
## 3.6      获取当前的模型对象实例      

### 函数:     getModel()    

	说明:

	*  @access  public
   
## 3.7      设置后续从主库读取数据      

### 函数:     readMaster($allTable = false)    

	说明:

	*  @access  public
   
	*  @param  bool  $allTable
  
## 3.8      获取当前的builder实例对象      

### 函数:     getBuilder()    

	说明:

	*  @access  public
   
## 3.9      指定默认的数据表名（不含前缀）      

### 函数:     name($name)    

	说明:

	*  @access  public
   
	*  @param  string  $name
  
## 3.10      指定默认数据表名（含前缀）      

### 函数:     setTable($table)    

	说明:

	*  @access  public
   
	*  @param  string  $table  表名

## 3.11      得到当前或者指定名称的数据表      

### 函数:     getTable($name = '')    

	说明:

	*  @access  public
   
	*  @param  string  $name
  
## 3.12      将SQL语句中的__TABLE_NAME__字符串替换成带前缀的表名（小写）      

### 函数:     parseSqlTable($sql)    

	说明:

	*  @access  public
   
	*  @param  string  $sql  sql语句

## 3.13      执行查询 返回数据集      

### 函数:     query($sql, $bind = [], $master = false, $class = false)    

	说明:

	*  @access  public
   
	*  @param  string  $sql  sql指令

	*  @param  array  $bind  参数绑定

	*  @param  boolean  $master  是否在主服务器读操作

	*  @param  bool|string  $class  指定返回的数据集对象

	*  @return  mixed
   
	*  @throws  BindParamException
   
## 3.14      执行语句      

### 函数:     execute($sql, $bind = [])    

	说明:

	*  @access  public
   
	*  @param  string  $sql  sql指令

	*  @param  array  $bind  参数绑定

	*  @return  int
   
	*  @throws  BindParamException
   
## 3.15      获取最近插入的ID      

### 函数:     getLastInsID($sequence = null)    

	说明:

	*  @access  public
   
	*  @param  string  $sequence  自增序列名

## 3.16      获取最近一次查询的sql语句      

### 函数:     getLastSql()    

	说明:

	*  @access  public
   
## 3.17      执行数据库事务      

### 函数:     transaction($callback)    

	说明:

	*  @access  public
   
	*  @param  callable  $callback  数据操作方法回调

## 3.18      启动事务      

### 函数:     startTrans()    

	说明:

	*  @access  public
   
## 3.19      用于非自动提交状态下面的查询提交      

### 函数:     commit()    

	说明:

	*  @access  public
   
	*  @return  void
   
## 3.20      事务回滚      

### 函数:     rollback()    

	说明:

	*  @access  public
   
	*  @return  void
   
## 3.21      批处理执行SQL语句      批处理的指令都认为是execute操作      

### 函数:     batchQuery($sql = [], $bind = [])    

	说明:

	*  @access  public
   
	*  @param  array  $sql  SQL批处理指令

## 3.22      获取数据库的配置参数      

### 函数:     getConfig($name = '')    

	说明:

	*  @access  public
   
	*  @param  string  $name  参数名称

## 3.23      得到分表的的数据表名      

### 函数:     getPartitionTableName($data, $field, $rule = [])    

	说明:

	*  @access  public
   
	*  @param  array  $data  操作的数据

	*  @param  string  $field  分表依据的字段

	*  @param  array  $rule  分表规则


