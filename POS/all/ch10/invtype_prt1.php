<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>���~���O���Ӫ�</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>
<body >
<!---�]�w�C�L����,�ǤJinvtype_prt2.php---------------------->	
<form name='form1' method='post' action='inv/invtype_prt2.php?prodtype=" . $row[prodtype] . "'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58" align="center" valign="middle">
		���~���O���Ӫ�
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133" align="center" >
		<br>
		���~���O�s��<br>		<p>
<!---�]�w�C�L����,��J���~���O�s���϶�---------------------->		
            <input type="text" name="prodtype" size="10" value="<?=$row['prodtype']?>"> 
        </p>
          <p>
            <input type="submit" name="Submit" value="�C�L" >
          </p>
          <p >&nbsp;          </p></td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
</body>
</html>
