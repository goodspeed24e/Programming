<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>���~���Ӫ�</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>

<body >
<!---�]�w�C�L����,�ǤJinvdtl_prt2.php-------------------->	
<form name='form1' method='post' action='inv/invdtl_prt2.php?prodno1=" . $row[prodno1] . "&prodno2=" . $row[prodno2] . "'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58" align="center" valign="middle">
		���~���Ӫ�
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133" align="center" >
		<br>
		���~�s��<br>		<p>
<!---�]�w�C�L����,��J���~�s���϶�---------------------->		
            <input type="text" name="prodno1" size="10" value="<?=$row['prodno1']?>">            
��
            <input type="text" name="prodno2" size="10" value="<?=$row['prodno2']?>">
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
