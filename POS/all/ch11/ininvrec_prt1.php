<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>進貨紀錄簿</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>

<body >
<!------ 傳給 ininvrec_prt2.php 檔案  ------>
<form name='form1' method='post' action='ininv/ininvrec_prt2.php?tranprodno1=" . $row[tranprodno1] . "&tranprodno2=" . $row[tranprodno2] . "'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58" align="center" valign="middle">
		進貨紀錄簿
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133" align="center" >
		<br>
		產品編號<br>		<p>
		<!--設定列印搜尋資料區間,輸入進貨日期------>	
            <input type="text" name="tranprodno1" size="10" value="<?=$row['tranprodno1']?>">            
至
            <input type="text" name="tranprodno2" size="10" value="<?=$row['tranprodno2']?>">
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
