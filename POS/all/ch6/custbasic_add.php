<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
//--------------------計數器取用----------	
	$cntid="cust";	
	include("counter.php");
	
//------------------ 將客戶類別資料表中的資料全部取出---------- 
	$SQLStr = "SELECT * FROM cuty";
	$res = mysql_query($SQLStr);	
?>
<!--------------資料欄位檢查--------------->
<script>
function validateForm(form1){
	if (!checkCustsname(form1.custsname)){
		alert("客戶簡稱 資料有誤，表單將不送出！");
		return(false);	
	}
	alert("資料正確無誤，立刻送出表單！");
	form.submit();
	return(true);
}
function checkCustsname(control) {
	ind = control.value.indexOf ('@', 0);
	if (control.value.length==0) {
		alert("請輸入客戶簡稱！");
		return (false);		
	} else
		return (true);
}
</script>
<!------進入custbasic_act.php 將客戶基本資料輸入資料庫中---------->
<form name="form1" method="post" action="cust/custbasic_act.php?func=insert">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td   bgcolor="#FFFFFF"> 
        <table width="780" border="1" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">新增客戶基本資料</font>
            </td> 
            <td align="center"> 
              <input type="submit" name="submit" value="新增客戶">
            </td>
	  </tr>
        </table>
        <table width="780" border="1" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr> 
            <td width="103" align="center">客戶序號</td>
            <td width="187"> 
                <input type="text" name="custno" size="10" value="<?=$custcnt;?>" >
            </td>
            <td width="96" align="center">客戶簡稱</td>
            <td width="351"> 
                <input type="text" name="custsname" size="30" onClick="checkCustsname">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">公司名稱</td>
            <td width="187"> 
                 <input type="text" name="custname" size="40">
            </td>
            <td width="96" align="center">負責人</td>
            <td width="351"> 
                <input type="text" name="custleader" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">統一編號</td>
            <td width="187"> 
                <input type="text" name="custinvoice" size="10">
            </td>
            <td width="96" align="center">聯絡人</td>
            <td width="351"> 
                <input type="text" name="custcontact" size="10">
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">聯絡電話</td>
            <td width="187"> 
                <input type="text" name="custtel" size="10">
            </td>
            <td width="96" align="center">聯絡手機</td>
            <td width="351"> 
                <input type="text" name="custmobil" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">傳真機</td>
            <td width="187" height="22"> 
              <input type="text" name="custfax" size="10">
            </td>
            <td width="96" height="22" align="center">客戶類別</td>           
            <td width="187" height="22">
<?php
	if ($res)
	{
	  $num = mysql_num_rows($res);
//--------------- 將客戶類別名稱的欄位值呈現於網頁上,供選擇--------------- 
          echo "<select name='custtype'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['cutyno'] . "'>" . $row['cutyname'] . "</option>";
	  }
            echo "</select>";
	}
//--------------- 客戶類別資料表中無類別資料---------------			
	else 
		echo "目前客戶無類別區分";
?>
              <input type="hidden" name="custdate" value="<?=date("Y-m-d")?>">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">業務員</td>
            <td width="187" height="22"> 
                <input type="text" name="custsales" size="10">
            </td>
		 </tr>
         <tr>
			<td width="103" height="22" align="center">公司地址</td>
            <td width="187" height="22"> 
                <input type="text" name="custadr" size="40">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">送貨地址</td>
            <td width="187" height="22"> 
                <input type="text" name="custpradr" size="40">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">發票地址</td>
            <td width="187" height="22"> 
                <input type="text" name="custinadr" size="40">
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">電子信箱</td>
            <td width="187"> 
                <input type="text" name="custemail" size="40">
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">網址</td>
            <td width="351"> 
                <input type="text" name="custhttp" size="40">
            </td>
          </tr>         
        </table>
        <br>        
      </td>
    </tr>
  </table>
</form>
</bady>
</html>