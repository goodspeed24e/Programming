<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>產品明細表</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>
<?php
$dt1=date("Y-m-d");
$dt2=date("Y-m-d");
?>
<body >
<!------ 傳給 ininvins_prt2.php 檔案  ------>
<form name='form1' method='post' action='ininv/ininvins_prt2.php?trandate1=" . $row[trandate1] . "&trandate2=" . $row[trandate2] . "'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58" align="center" valign="middle">
		進貨日報表
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133" align="center" >
		<br>
		進貨日期<br> 	<p>
	<!--設定列印搜尋資料區間,輸入進貨日期------>		
            <input type="text" name="trandate1" size="10" value="<?=$dt1; ?>">            
至
            <input type="text" name="trandate2" size="10" value="<?php echo $dt2 ?>">
        </p>
          <p>
            <input type="submit" name="Submit" value="列印" >
          </p>
          <p >&nbsp;          </p></td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
</body>
</html>
