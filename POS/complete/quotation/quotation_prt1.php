<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body >
<?php 
    // -------------���X�Ҧ��������---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  quotationwork";
	$res = mysql_query($SQLStr);
	
    //--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!------�ǵ�quotation_prt2.php,����C�L---->
<form name="form1" method="post" action="quotation/quotation_prt2.php?quwkno=' . $quwkno . '">
  <table width="782" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
    //--------------���ƿ�ܧe�{�γs��---------------
     echo "�C�L��������&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=180&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?>
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             �����渹
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             �Ȥ�
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ��f���
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �P�����O
            </td>             
          </tr>		  
	<?php
      //--------------��ܭ��Ƴ������Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from quotationwork order by quwkno limit $first , 10";
	  $res = mysql_query($SQLStr);	 
        while (list($quwkno, $quwkprod, $quwkcust, $quwktype, $quwkpric, $quwkqty, $quwksqty, $quwksdate, $quwkunit, $quwkprodname, $quwkcustname)=mysql_fetch_row($res))
		{
        //-------------- ����������ƪ���ƨçe�{-----------------
            echo "<tr border='0'   bgcolor='#ffffff'>";			
			echo "<td align='center'><a href='quotation/quotation_prt2.php?quwkno=" . $quwkno . "&quwkprodno=".$quwkprodno ."&quwkcust=".$quwkcust."&quwkcustname=".$quwkcustname."&quwktype=".$quwktype."&quwksdate=".$quwksdate."'>" . $quwkno . "</a></td>\n";
			echo "<td align='center'>" . $quwkcust  ."/" . $quwkcustname . "</td>\n";
			echo "<td align='center'>";
			   if ($quwksdate == '') 
			      $quwksdate="�L���";	        
			      echo  $quwksdate . "</td>\n";
            echo "<td align='center'>";			  
			   if ($quwktype == '') 
			      $quwktype="�ӺD��";	        
			      echo  $quwktype . "</td>\n";
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
