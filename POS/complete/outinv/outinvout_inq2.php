<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>Web base進銷存管理系</title>
</head>
<body>
<?php
    include("mysqlcntdb.php");

	//---------------- 將 product 及 outinv 結合------------------------------
	$SQLStr = "SELECT outinv.*, product.* FROM outinv AS outinv ";
	$SQLStr .= "LEFT JOIN  product AS  product ON outinv.outiprodno = product.prodno WHERE (outino='$outino' and outiprodno='$outiprodno')";
	$res = mysql_query($SQLStr);	
	
	//------------------- 判斷搜尋結果是否有值-----------------------------
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
	
?>
<!------回主目錄 ,傳給 index.php 檔案  ------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr>	  
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">銷貨詳細資訊</font>
            </td>                
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="搜尋銷貨資料完成,回首頁">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr>           
            <td width="241" align="center"><font >銷貨單號</font></td>
            <td width="522" align="left"><?=$row['outino']?> 		      
            </td>            
          </tr>
          <tr> 
            <td width="241" align="center"><font >產品編號</font></td>
            <td width="522" align="left"><?=$row['outiprodno']?>			    
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >產品名稱</font></td>
            <td width="522" align="left"><?=$row['prodname']?>			   	   
            </td>
          </tr>         
          <tr>
            <td width="241" height="22" align="center"><font >銷貨日期</font> </td>
            <td width="522" height="22" align="left"><?=$row['outidate']?>                
            </td>            
          </tr>
          <tr>            
            <td width="241" height="22" align="center">客戶編號</td>
            <td width="522" height="22" align="left"><?=$row['outicustno']?>
			<input type="hidden" name="outicustno" size="10" value="<?=$row['outicustno']?>"> 		
            </td>			           
          </tr>
		 
		  <tr>            
            <td width="241" height="22" align="center">報價單號</td>
            <td width="522" height="22" align="left"><?=$row['outipono']?>			
			</td>			           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">產品數量</td>
            <td width="522" height="22"><?=$row['outiprodqty']?></td>           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">產品單位</td>
            <td width="522" height="22"><?=$row['outiunit']?> 
             </td>           
          </tr>
		  <tr> 
            <td width="241" align="center">單價</td>
            <td width="522"><?=$row['outipric']?> 
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
	 $msg="無此銷貨單";
	 include("windowsclose.php");		
	}
?>
</body>
</html>