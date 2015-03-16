<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php   
    include("mysqlcntdb.php");
	//----------取出 進貨及產品資料---------	
	$SQLStr = "SELECT transaction.*, product.* FROM transaction  AS transaction  ";
	$SQLStr .= "LEFT JOIN product AS product ON transaction.tranprodno = product.prodno WHERE (tranno='$tranno' and tranpono='$tranpono' and tranprodno='$tranprodno')";
	$res = mysql_query($SQLStr);
		
    //------- 判斷搜尋結果是否有值------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<script language="JavaScript">
//-------------- 檢查產品數量--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("產品數量空白");
      fld.focus();
      fld.select();
   }
}
//-------------- 檢查產品單價--------------
function checkpric(fld){
   if (fld.value == ""){
      alert("產品單價欄位為空白");
      fld.focus();
      fld.select();
   }
}
</script>
<?php $oqty=$row['tranprodqty'];  
       $opric=$row['tranpric']; 
       $ovend=$row['tranvendno']; 
?> 
<!------ 連接資料庫,傳給 ininvins_mod3.php 檔案 ------>
<form name="form1" method="post" action="ininvins_mod3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr bgcolor="#FFFFFF"> 
      <td >  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">進貨詳細資訊</font>
            </td>
                   
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="修改進貨資料">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr>           
            <td width="241" align="center"><font >進貨單號</font></td>
            <td width="522" align="left"><?=$row['tranno']?> 
			  <input  type="hidden" name="tranno" size="10" value="<?=$row['tranno']?>">
		      <input  type="hidden" name="oqty" size="10" value="<?=$oqty;?>">
			  <input  type="hidden" name="opric" size="10" value="<?=$opric;?>">
			  <input  type="hidden" name="ovend" size="10" value="<?=$ovend;?>">			 
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
			    <input type="hidden" name="tranprodname" size="40" value="<?=$row['prodname']?>">			   
            </td>
          </tr>
          <tr>
            <td width="241" align="center"><font >採購單號</font> </td>
            <td width="522" align="left"><?=$row['tranpono']?>
                <input type="hidden" name="tranpono" size="10" value="<?=$row['tranpono']?>">
            </td>            
          </tr>
		   <tr>            
            <td width="241" height="22" align="center">廠商編號</td>
            <td width="522" height="22" align="left"><?=$row['tranvendno']?>
                <input type="hidden" name="tranvendno" size="10" value="<?=$row['tranvendno']?>">
            </td>			           
          </tr>
          <tr>
            <td width="241" height="22" align="center"><font >進貨日期</font> </td>
            <td width="522" height="22" align="left">
                <input type="text" name="trandate" size="10" value="<?=$row['trandate']?>">
            </td>            
          </tr>         
		  <tr>
			<td width="241" height="22" align="center">產品數量</td>
            <td width="522" height="22">
			    <!------------------ 修改並檢查產品數量--------------> 
                <input type="text" name="tranprodqty" size="6" value="<?=$row['tranprodqty']?>"  onblur="checkprodqty(this)">
            </td>           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">產品單位</td>
            <td width="522" height="22"> 
                <input type="text" name="tranunit" size="10" value="<?=$row['tranunit']?>">
            </td>           
          </tr>
		  <tr> 
            <td width="241" align="center">產品單價</td>
            <td width="522">
			    <!---------------- 修改並檢查產品單價-------------->
                <input type="text" name="tranpric" size="10" value="<?=$row['tranpric']?>"   onBlur="checkpric(this)" >
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
