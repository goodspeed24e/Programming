<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
	//----------------- 將 product 及 quotationwork 結合起來--------------
	$SQLStr = "SELECT quotationwork.*, product.*  FROM quotationwork AS  quotationwork ";
	$SQLStr .= "LEFT JOIN  product AS  product ON quotationwork.quwkprod = product.prodno WHERE (quwkno='$quwkno' and quwkprod='$quwkprod' and quwkcust='$quwkcust')";
	$res = mysql_query($SQLStr);
	
	//---------- 判斷搜尋結果是否有值-----------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!------ 完成搜尋,傳給主目錄------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">報價詳細資訊</font>
            </td>                 
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="搜尋報價資料完成,回首頁">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" bordercolor="#0000FF">
          <tr>           
            <td width="241" align="center"><font >報價單號</font></td>
            <td width="522" align="left"><?=$row['quwkno']?> 
		      <input  type="hidden" name="quwkno" size="10" value="<?=$row['quwkno']?>">
            </td>            
          </tr>
          <tr> 
            <td width="241" align="center"><font >產品編號</font></td>
            <td width="522" align="left"><?=$row['quwkprod']?>
			    <input type="hidden" name="quwkprod" size="10" value="<?=$row['quwkprod']?>">
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >產品名稱</font></td>
            <td width="522" align="left"><?=$row['prodname']?>			   	   
            </td>
          </tr>
		   <tr> 
            <td width="241" align="center"><font >客戶編號</font></td>
            <td width="522" align="left"><?=$row['quwkcust']?>
			    <input type="hidden" name="quwkcust" size="10" value="<?=$row['quwkcust']?>">
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >報價類別</font></td>
            <td width="522" align="left"><?=$row['quwktype']?>			  
            </td>
          </tr>
		  <tr>
			<td width="241" height="22" align="center">報價數量</td>
            <td width="522" height="22"><?=$row['quwkqty']?>               
            </td>           
          </tr>
		   <tr> 
            <td width="241" align="center">售價</td>
            <td width="522"><?=$row['quwkpric']?>              
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
	 $msg="無此報價單";
	 include("windowsclose.php");
	}
?>
</body>
</html>
