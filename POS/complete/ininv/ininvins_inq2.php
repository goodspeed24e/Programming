<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
	//----------取出符合條件進貨單資料---------
	$SQLStr = "SELECT * FROM transaction  WHERE (tranno='$tranno' and tranpono='$tranpono' and tranprodno='$tranprodno')";
	$res = mysql_query($SQLStr);
		
    //----------- 判斷搜尋結果是否有值--------------------
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
?>
<!------ 回首頁,傳給 index.php  ------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center">
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="50%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">進貨詳細資訊</font>
            </td>
            <td align="center"> 
              <input type="submit" name="submit" value="搜尋進貨資料結束,回首頁">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr>           
            <td width="241" align="center"><font >進貨單號</font></td>
            <td width="522" align="left"><?=$row['tranno']?>		     
            </td>
          </tr>
          <tr> 
            <td width="241" align="center"><font >產品編號</font></td>
            <td width="522" align="left"><?=$row['tranprodno']?>			  
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
