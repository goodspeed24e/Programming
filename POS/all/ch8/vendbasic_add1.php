<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?	
	include("mysqlcntdb.php");
	$cntid="vend";
	include("counter.php");
//----------------------- 將廠商類別資料表中的資料全部取出-------------------------- 
	$SQLStr = "SELECT * FROM vety";
	$res = mysql_query($SQLStr);
	
?>
<!--執行廠商基本資料輸入後,進入vendbasic_add2.php連接資料庫------->
<form name="form1" method="post" action="vend/vendbasic_add2.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td bgcolor="#ffffff"> 
        <table width="780" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">廠商基本資料</font>
            </td>
            <td align="center"> 
              <input type="submit" name="submit" value="新增廠商">
            </td>
	  </tr>
        </table>
<!--廠商基本資料輸入------->		
        <table width="780" border="1" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr> 
            <td width="103" align="center">廠商序號</td>
            <td width="187"> 
                <input type="text" name="vendno" size="10" value="<?=$vendcnt;?>">
            </td>
            <td width="96" align="center">廠商簡稱</td>
            <td width="351"> 
                <input type="text" name="vendsname" size="30">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">公司名稱</td>
            <td width="187"> 
                 <input type="text" name="vendname" size="40">
            </td>
            <td width="96" align="center">負責人</td>
            <td width="351"> 
                <input type="text" name="vendleader" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">統一編號</td>
            <td width="187"> 
                <input type="text" name="vendinvoice" size="10">
            </td>
            <td width="96" align="center">聯絡人</td>
            <td width="351"> 
                <input type="text" name="vendcontact" size="10">
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">聯絡電話</td>
            <td width="187"> 
                <input type="text" name="vendtel" size="10">
            </td>
            <td width="96" align="center">聯絡手機</td>
            <td width="351"> 
                <input type="text" name="vendmobil" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">傳真機</td>
            <td width="187" height="22"> 
              <input type="text" name="vendfax" size="10">
            </td>
            <td width="96" height="22" align="center">廠商類別</td>
           <!-- </td>-->
            <td width="187" height="22">
<?
	if ($res)
	{
	  $num = mysql_num_rows($res);
//---------- 將廠商類別名稱的欄位值呈現於網頁上,供選擇-------------- 
          echo "<select name='vendtype'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['vetyno'] . "'>" . $row['vetyname'] . "</option>";
	  }
            echo "</select>";	
	}			
	else 
		echo "目前廠商無類別區分";
?>
              <input type="hidden" name="venddate" value="<?=date("Y-m-d")?>">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">採購擔當</td>
            <td width="187" height="22"> 
                <input type="text" name="vendsales" size="10">
            </td>
		 </tr>
         <tr>
			<td width="103" height="22" align="center">公司地址</td>
            <td width="187" height="22"> 
                <input type="text" name="vendadr" size="40">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">出貨地址</td>
            <td width="187" height="22"> 
                <input type="text" name="vendpradr" size="40">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">發票地址</td>
            <td width="187" height="22"> 
                <input type="text" name="vendinadr" size="40">
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">電子信箱</td>
            <td width="187"> 
                <input type="text" name="vendemail" size="40">
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">網址</td>
            <td width="351"> 
                <input type="text" name="vendhttp" size="40">
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
