<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>產品類別明細表</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>
<?php
$dt1=date("Y-m-d");
?>
<body >
<!---設定列印條件,傳入invproc_prt2.php---------------------->	
<form name='form1' method='post' action='inv/invproc_prt2.php'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58" align="center" valign="middle">
		呆滯產品處理表
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133" align="center" >
		<br>
		最後異動日期<br>		<p>
<!---設定列印條件,輸入最後異動日期區間---------------------->			
            <input type="text" name="proddate" size="10" value="<?=$dt1?>">         
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
