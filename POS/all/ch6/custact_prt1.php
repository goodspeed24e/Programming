<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>客戶會計科目設定</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>
<body>
<form name='form1' method='post' action='cust/custact_prt2.php?custno1=" . $row[custno1] . "&custno2=" . $row[custno2] . "'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58"   align="center" valign="middle">
		客戶會計科目設定表
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133" align="center" >
		<br>
		客戶編號<br>		<p>
            <input type="text" name="custno1" size="10" value="<?=$row['custno1']?>">            
至
            <input type="text" name="custno2" size="10" value="<?=$row['custno2']?>">
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
