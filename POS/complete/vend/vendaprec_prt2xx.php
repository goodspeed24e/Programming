<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��vendaprec_prt2</title>
</head>
<body onLoad="window.print()">
<?php
// ------------------���X�Ҧ��i�f�檺���---------------
	include("mysqlcntdb.php");
//------------------- �̷j�M������X, �i�f��Ƥ��e ---------------
	$SQLStr = "SELECT transaction.* FROM transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2' and tranvendno='$tranvendno') ";	
	$res = mysql_query($SQLStr);

	
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!----����C�L����,�^����----------->
<form name="form1" method="post" action="../index.php?Select=10">

  <table width="782" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�t�����I�b�ڪ�&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
	    echo "�t�ӽs��:".$tranvendno." ";
		echo "  <a href=index.php?Select=248&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?>   
	  
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="0" align="center" bgcolor="#FFFFFF">
          <tr> 
		     <td width="114" align="center" bgcolor="#99CCFF"> 
              �i�f���
            </td>                     
            <td width="114" align="center" bgcolor="#99CCFF"> 
             �i�f�渹 
            </td>
            <td width="114" align="center" bgcolor="#99CCFF">���~�s�� 
            </td>           
            <td width="114" align="center" bgcolor="#99CCFF">���~�W��  
            </td>			
			<td width="63" align="center" bgcolor="#99CCFF">�ƶq 
            </td> 
			 <td width="63" align="center" bgcolor="#99CCFF">��� 
            </td>  
			 <td width="73" align="center" bgcolor="#99CCFF"> 
              ���B</td>      
			                  
          </tr>		  
	<?php
//--------------��ܭ��Ƽt�Ӷi�f���Ƨe�{�γs���C�L�����\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from transaction WHERE (trandate >='$trandate1' and trandate<='$trandate2' and tranvendno='$tranvendno') limit $first , 10";
	  $res = mysql_query($SQLStr);	
	   while (list($trancode, $trandate, $tranno, $tranpono, $tranremark, $tranvendno, $tranprodno, $tranprodname, $tranprodqty, $tranunit, $tranpric, $tranamt)=mysql_fetch_row($res))
		{
//--------------- �����ƪ���ƨæC�L------------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $trandate . "</td>\n";
			echo "<td align='center'>" . $tranno . "</td>\n";
			echo "<td align='center'>" . $tranprodno  . "</td>\n";
			echo "<td align='center'>" . $tranprodname . "</td>\n";
			echo "<td align='center'>" . $tranprodqty . "</td>\n";			
			echo "<td align='center'>" . $tranpric . "</td>\n";
			echo "<td align='center'>" . $tranamt . "</td>\n";
			echo "</tr>";		  	
		}	
?>      
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
