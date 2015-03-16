<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");	
    //-------------- 將採購主資料表中的資料符合採購編號的資料取出--------------
	$SQLStr = "SELECT purchmst.* FROM purchmst  WHERE purcmtranno='$purcmtranno'";	
	$res = mysql_query($SQLStr);

 while (list($purcmtranno, $purcmvend, $purcmdate, $purcmtype)=mysql_fetch_row($res))
 {
 ?>
 <!------ 傳給 purchmst_del3.php 檔案 ------>
<form name="form1" method="post" action="purchmst_del3.php?purcmtranno='.$purcmtranno.'">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center">
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">刪除採購主資料表中資料</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="刪除採購主資料表中資料">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="103" align="center">採購單號</td>
            <td width="187"><?=$purcmtranno; ?>
			 <input  type="hidden" name="purcmtranno" size="10" value="<?=$purcmtranno;?>">                
            </td>
		 </tr>	
		 <tr>
            <td width="96" align="center">供應廠商</td>
            <td width="351"><?=$purcmvend; ?>               
            </td>
          </tr>        
          <tr>            
            <td width="96" height="22" align="center">交貨日期</td>
			 <td width="351"><?=$purcmdate; ?>               
            </td>
			
		  </tr>        
          <tr> 
			 <td width="96" align="center">採購類別</td>
            <td width="351"><?=$purcmtype; ?>              
            </td>
          </tr> 
		</table>  
      </td>
    </tr>
  </table>
</form>
<?php
}
?>
</body>
</html>
 