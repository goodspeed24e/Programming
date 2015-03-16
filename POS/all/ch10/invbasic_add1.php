<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?	
	include("mysqlcntdb.php");
	$cntid="prod";
	include("counter.php");
	// -------------取出所有產品類別的資料---------------
	$SQLStr = "SELECT * FROM prty";
	$res = mysql_query($SQLStr);	
?>
<!------資料檢查,檢查輸入欄位資料正確性----------------------->
<script language="JavaScript">
function validate(){
   var jfm = document.form1;
   var prodno = jfm.prodno[].value;  
   if (prodno == "" ){
      alert("沒有輸入產品編號!");
      event.returnValue = false;
   }   
}
// --------------檢查產品編號--------------
function checkprodno(fld){
   if (fld.value.length < 1){
      alert("請輸入產品編號(大於1個字元)!");
      fld.focus();
      fld.select();
   }
}

//-------------- 檢查數量--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("請輸入產品數量!");
      fld.focus();
      fld.select();
   }
}

//-------------- 檢查單價--------------
function checkpric(fld){
   if (fld.value == ""){
      alert("請輸入單價!");
      fld.focus();
      fld.select();
   }
}
</script>	
<!--執行產品基本資料輸入後,進入invdbasic_add2.php連接資料庫------->
<form name="form1" method="post" action="inv/invbasic_add2.php" onSubmit="validate();">
 <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr>
	  <td   bgcolor="#FFFFFF">  
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">新增產品基本資料</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="新增產品資料">
            </td>                 
          </tr>
        </table>
<!--產品基本資料輸入------->		
        <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"   bordercolor="#FFFFFF" align="center">
          <tr> 
            <td width="103" align="center">產品編號</td>
            <td width="187"> 
                <input type="text" name="prodno" size="10" value="<?=$prodcnt;?>"  onChange="checkprodno(this)">
            </td>
            <td width="96" align="center">產品名稱</td>
            <td width="351"> 
                <input type="text" name="prodname" size="40">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">規格說明</td>
            <td width="187"> 
                 <input type="text" name="prodsdesp" size="40">
            </td>
            <td width="96" align="center">產品類別</td>
            <td width="351">
<?php

	if ($res)
	{
	  $num = mysql_num_rows($res);
//------------------- 呈現類別名稱的欄位值,供選擇------------------------------------
          echo "<select name='prodtype'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['prtyno'] . "'>" . $row['prtyname'] . "</option>";
	  }
            echo "</select>";
	
	}		
	else 
		echo "目前產品無類別區分";
?>              
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">供應廠商</td>
            <td width="187">
<?php
//-------------------- 將廠商資料表中的資料全部取出----------------------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res);
//------------------- 呈現廠商名稱的欄位值,供選擇------------------------------------
           echo "<select name='prodvend'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['vendno'] . "'>" . $row['vendname'] . "</option>";
	  }
            echo "</select>";	
	}		
	else 
		echo "目前廠商無名稱";
?>
            </td>
            <td width="96" align="center">單位</td>
            <td width="351">
<?php
//-------------------- 將產品單位資料表中的資料全部取出----------------------------
	$SQLStr = "SELECT * FROM prun";
	$res = mysql_query($SQLStr);	
	if ($res)
	{
	  $num = mysql_num_rows($res);
//------------------- 呈現產品單位名稱的欄位值,供選擇------------------------------------
      echo "<select name='produnit'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['prunno'] . "'>" . $row['prunname'] . "</option>";
	  }
            echo "</select>";
	}		
	else 
		echo "目前產品單位無區分";
?>	       
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">成本價格</td>
            <td width="187"> 
                <input type="text" name="prodipric" size="10"  onChange="checkpric(this)">
            </td>
            <td width="96" align="center">售價</td>
            <td width="351"> 
                <input type="text" name="prodspric" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">安全存量</td>
            <td width="187" height="22"> 
              <input type="text" name="prodsave" size="10">
            </td>
            <td width="96" height="22" align="center">最近進貨日</td>              
            <td width="187" height="22">
              <input type="text" name="prodidate" value="<?=date("Y-m-d")?>">
            </td>
          </tr>         
         <tr>
			<td width="103" height="22" align="center">最近出貨日</td>
            <td width="187" height="22"> 
			<input type="text" name="prododate" value="<?=date("Y-m-d")?>">                
            </td>           
          </tr>		     
        </table>
        <br>        
      </td>
    </tr>
  </table>
</form>
</body>
</html>
