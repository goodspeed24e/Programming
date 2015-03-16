<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>廠商會計科目設定vendact_prt1</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>

<body>
<form name='form1' method='post' action='vend/vendact_prt2.php?vendno1=" . $row[vendno1] . "&vendno2=" . $row[vendno2] . "'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58"   align="center" valign="middle">
		廠商會計科目設定表
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133" align="center" >
<!--輸入列印條件,廠商編號------------>		
		<br>
		廠商編號<br>		<p>
            <input type="text" name="vendno1" size="10" value="<?=$row['vendno1']?>">            
至
            <input type="text" name="vendno2" size="10" value="<?=$row['vendno2']?>">
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
