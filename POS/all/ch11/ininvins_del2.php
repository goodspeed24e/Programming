<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
	//----------取出符合條件的所有進貨的資料---------	
	$SQLStr = "SELECT * FROM transaction  WHERE (tranno='$tranno' and tranpono='$tranpono' and tranprodno='$tranprodno')";
	$res = mysql_query($SQLStr);
		
	//------------------------ 判斷搜尋結果是否有值--------------------------------
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
?>
<!------ 執行刪除作業,傳給ininvins_del3.php 檔案,連接資料庫 ------>
<form name="form1" method="post" action="ininvins_del3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">進貨詳細資訊</font>
            </td>                      
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="刪除進貨資料">
            </td>
	  </tr>
  </table>
<!--呈現進貨資料,供判斷---------->  
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr>           
            <td width="241" align="center"><font >進貨單號</font></td>
            <td width="522" align="left"><?=$row['tranno']?>	
			 <input  type="hidden" name="tranno" size="10" value="<?=$row['tranno']?>">     
            </td>            
          </tr>
          <tr> 
            <td width="241" align="center"><font >產品編號</font></td>
            <td width="522" align="left"><?=$row['tranprodno']?>
			 <input type="hidden" name="tranprodno" size="10" value="<?=$row['tranprodno']?>">   
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >產品名稱</font></td>
            <td width="522" align="left"><?=$row['prodname']?>			    		   
            </td>
          </tr>
          <tr>
            <td width="241" align="center"><font >採購單號</font> </td>
            <td width="522" align="left"><?=$row['tranpono']?> 
			  <input type="hidden" name="tranpono" size="10" value="<?=$row['tranpono']?>">              
            </td>            
          </tr>
          <tr>
            <td width="241" height="22" align="center"><font >進貨日期</font> </td>
            <td width="522" height="22" align="left"><?=$row['trandate']?>                
            </td>            
          </tr>
          <tr>            
            <td width="241" height="22" align="center">廠商編號</td>
            <td width="522" height="22" align="left"><?=$row['tranvendno']?>
			<input type="hidden" name="tranvendno" size="10" value="<?=$row['tranvendno']?>">                  
            </td>			           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">產品數量</td>
            <td width="522" height="22"><?=$row['tranprodqty']?>			               
            </td>           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">產品單位</td>
            <td width="522" height="22"><?=$row['tranunit']?>              
            </td>           
          </tr>
		  <tr> 
            <td width="241" align="center">單價</td>
            <td width="522"><?=$row['tranpric']?>			            
            </td>
		  </tr>		   
		</td>
    </tr> 
  </table>
</form>
<?
}
else
	{
	 $msg="無此進貨單";
	 include("windowsclose.php");
	}
?>
</body>
</html>


